#include "irrsdl00.hpp"

namespace SEAR {
void IRRSDL00::callIRRSDL00(keyring_args_t *p_args,
                            uint32_t *p_parmlist_version, void *p_parmlist) {
  uint32_t nNumParms = 14;

  IRRSDL64(&nNumParms, &p_args->RACF_work_area[0], p_args->ALET_SAF_rc,
           &p_args->SAF_rc, p_args->ALET_RACF_rc, &p_args->RACF_rc,
           p_args->ALET_RACF_rsn, &p_args->RACF_rsn, &p_args->function_code,
           &p_args->attributes, &p_args->RACF_user_id[0], &p_args->ring_name[0],
           p_parmlist_version, p_parmlist);
}

void IRRSDL00::extractKeyring(SecurityRequest &request,
                              keyring_extract_arg_area_t *p_arg_area_keyring) {
  uint32_t parmlist_version = 0;

  auto result_unique_ptr =
      std::make_unique<char[]>(sizeof(keyring_extract_parms_results_t));
  std::memset(result_unique_ptr.get(), 0,
              sizeof(keyring_extract_parms_results_t));
  p_arg_area_keyring->p_result_buffer =
      reinterpret_cast<keyring_extract_parms_results_t *>(
          result_unique_ptr.get());
  p_arg_area_keyring->p_result_buffer->result_buffer_length =
      sizeof(keyring_extract_parms_results_t);
  request.setRawResultLength(
      p_arg_area_keyring->p_result_buffer->result_buffer_length);

  keyring_extract_parms_results_t *p_result_buffer =
      p_arg_area_keyring->p_result_buffer;

  cddlx_get_ring_t *p_parm_get_ring = &p_result_buffer->result_buffer_get_ring;

  p_arg_area_keyring->args.function_code = 0x0D;
  p_arg_area_keyring->args.attributes    = 0;

  p_parm_get_ring->cddlx_ring_res_len    = RING_INFO_BUFFER_SIZE;
  p_parm_get_ring->cddlx_ring_res_ptr =
      &p_result_buffer->union_ring_result.ring_result;

  Logger::getInstance().debug("cddlx_get_ring_t before call");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_parm_get_ring),
                                sizeof(cddlx_get_ring_t));

  IRRSDL00::callIRRSDL00(&p_arg_area_keyring->args, &parmlist_version,
                         p_parm_get_ring);

  Logger::getInstance().debug("cddlx_get_ring_t after call");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_parm_get_ring),
                                sizeof(cddlx_get_ring_t));

  Logger::getInstance().debug("Ring result (first 256)");
  Logger::getInstance().hexDump(
      reinterpret_cast<char *>(p_parm_get_ring->cddlx_ring_res_ptr), 256);

  if (p_arg_area_keyring->args.SAF_rc <= 4 &&
      p_arg_area_keyring->args.RACF_rc <= 4 &&
      p_arg_area_keyring->args.RACF_rsn == 0) {
    ring_result_t *p_ring_result =
        &p_result_buffer->union_ring_result.ring_result;

    int ring_count = ntohl(p_ring_result->ring_count);

    unsigned char *work =
        reinterpret_cast<unsigned char *>(&p_ring_result->ring_info);
    int help_len = 0;

    for (int i = 0; i < ring_count; i++) {
      // Count ring owner
      help_len += 1 + *work;
      work += 1 + *work;

      // Count ring name
      help_len += 1 + *work;
      work += 1 + *work;

      // Count cert count
      help_len += 4;
      unsigned int certCount = ntohl(*(reinterpret_cast<uint32_t *>(work)));
      work += 4;

      p_result_buffer->cert_count += certCount;

      for (int j = 0; j < certCount; j++) {
        // Count cert owner
        help_len += 1 + *work;
        work += 1 + *work;

        // Count cert name
        help_len += 1 + *work;
        work += 1 + *work;
      }
    }

    p_result_buffer->ring_info_length = help_len;

    if (p_result_buffer->cert_count > 0) {
      // Reallocate memory with a larger block to include DataGetFirst results
      // per cert
      int result_len =
          p_result_buffer->result_buffer_length +
          (p_result_buffer->cert_count * sizeof(get_cert_buffer_t));
      auto result2_unique_ptr = std::make_unique<char[]>(result_len);
      p_result_buffer = reinterpret_cast<keyring_extract_parms_results_t *>(
          result2_unique_ptr.get());
      std::memset(p_result_buffer, 0, result_len);
      std::memcpy(p_result_buffer, p_arg_area_keyring->p_result_buffer,
                  sizeof(keyring_extract_parms_results_t));
      result_unique_ptr.reset();
      p_arg_area_keyring->p_result_buffer   = p_result_buffer;
      p_result_buffer->result_buffer_length = result_len;
      p_result_buffer->result_buffer_get_ring.cddlx_ring_res_ptr =
          &p_result_buffer->union_ring_result.ring_result;
      p_ring_result = &p_result_buffer->union_ring_result.ring_result;

      get_cert_buffer_t *p_get_cert_buffer =
          reinterpret_cast<get_cert_buffer_t *>(
              (((uint64_t)p_result_buffer) +
               sizeof(keyring_extract_parms_results_t)));
      p_result_buffer->p_get_cert_buffer = p_get_cert_buffer;

      int get_cert_index                 = 0;

      bool keep_going                    = true;

      work = reinterpret_cast<unsigned char *>(&p_ring_result->ring_info);

      for (int i = 0; keep_going && i < ring_count; i++) {
        // Ring owner
        work += 1 + *work;

        // Ring name
        work += 1 + *work;

        // Cert count
        unsigned int certCount = ntohl(*(reinterpret_cast<uint32_t *>(work)));
        work += 4;

        for (int j = 0; keep_going && j < certCount; j++) {
          // Cert owner
          unsigned char *p_owner = work;
          work += 1 + *work;

          // Cert name
          unsigned char *p_label = work;
          work += 1 + *work;

          IRRSDL00::extractCert(request, p_arg_area_keyring, p_get_cert_buffer,
                                p_owner, p_label);

          if (p_arg_area_keyring->args.SAF_rc <= 4 &&
              p_arg_area_keyring->args.RACF_rc <= 4 &&
              p_arg_area_keyring->args.RACF_rsn == 0) {
            get_cert_index++;
            p_get_cert_buffer = reinterpret_cast<get_cert_buffer_t *>(
                (((uint64_t)p_get_cert_buffer) + sizeof(get_cert_buffer_t)));
          } else {
            keep_going = false;
          }
        }
      }

      request.setRawResultPointer(result2_unique_ptr.get());
      result2_unique_ptr.release();
      request.setRawResultLength(
          p_arg_area_keyring->p_result_buffer->result_buffer_length);
    } else {
      request.setRawResultPointer(result_unique_ptr.get());
      result_unique_ptr.release();
      request.setRawResultLength(
          p_arg_area_keyring->p_result_buffer->result_buffer_length);
    }
  } else {
    request.setRawResultPointer(result_unique_ptr.get());
    result_unique_ptr.release();
    request.setRawResultLength(
        p_arg_area_keyring->p_result_buffer->result_buffer_length);
  }

  request.setSAFReturnCode(p_arg_area_keyring->args.SAF_rc);
  request.setRACFReturnCode(p_arg_area_keyring->args.RACF_rc);
  request.setRACFReasonCode(p_arg_area_keyring->args.RACF_rsn);
}

void IRRSDL00::extractCert(const SecurityRequest &request,
                           keyring_extract_arg_area_t *p_arg_area_keyring,
                           get_cert_buffer_t *p_get_cert_buffer,
                           unsigned char *p_owner, unsigned char *p_label) {
  uint32_t parmlist_version_ = 1;

  keyring_extract_parms_results_t *p_result_buffer =
      p_arg_area_keyring->p_result_buffer;

  cddlx_get_cert_t *p_parm_get_cert =
      &p_get_cert_buffer->result_buffer_get_cert;

  p_arg_area_keyring->args.function_code       = 1;
  p_arg_area_keyring->args.attributes          = 0xA0000000;

  p_result_buffer->handle_map.cddlx_predicates = 1;
  p_result_buffer->handle_map.cddlx_attr_id    = 1;  // match on label
  p_result_buffer->handle_map.cddlx_attr_len   = *p_label;
  p_result_buffer->handle_map.cddlx_attr_ptr   = &p_label[1];

  p_parm_get_cert->cddlx_res_handle            = &p_result_buffer->handle_map;
  p_parm_get_cert->cddlx_cert_len              = CERT_BUFFER_SIZE;
  p_parm_get_cert->cddlx_cert_ptr =
      reinterpret_cast<unsigned char *>(&p_get_cert_buffer->cert_buffer[0]);
  p_parm_get_cert->cddlx_pk_len = PKEY_BUFFER_SIZE;
  p_parm_get_cert->cddlx_pk_ptr =
      reinterpret_cast<unsigned char *>(&p_get_cert_buffer->pkey_buffer[0]);
  p_parm_get_cert->cddlx_label_len = LABEL_BUFFER_SIZE;
  p_parm_get_cert->cddlx_label_ptr =
      reinterpret_cast<unsigned char *>(&p_get_cert_buffer->label_buffer[0]);
  p_parm_get_cert->cddlx_racf_userid[0] = 8;
  p_parm_get_cert->cddlx_sdn_len        = SDN_BUFFER_SIZE;
  p_parm_get_cert->cddlx_sdn_ptr =
      reinterpret_cast<unsigned char *>(&p_get_cert_buffer->cert_sdn_buffer[0]);
  p_parm_get_cert->cddlx_recid_len = RECID_BUFFER_SIZE;
  p_parm_get_cert->cddlx_recid_ptr = reinterpret_cast<unsigned char *>(
      &p_get_cert_buffer->cert_recid_buffer[0]);

  Logger::getInstance().debug("Keyring extract request buffer:");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area_keyring),
                                request.getRawRequestLength());

  Logger::getInstance().debug("cddlx_get_cert_t before call");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_parm_get_cert),
                                sizeof(cddlx_get_cert_t));

  IRRSDL00::callIRRSDL00(&p_arg_area_keyring->args, &parmlist_version_,
                         p_parm_get_cert);

  Logger::getInstance().debug("cddlx_get_cert_t after call");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_parm_get_cert),
                                sizeof(cddlx_get_cert_t));
}

void IRRSDL00::addOrDeleteKeyring(
    SecurityRequest &request, keyring_modify_arg_area_t *p_arg_area_keyring) {
  uint32_t parmlist_version = 0;

  if (request.getOperation() == "add") {
    p_arg_area_keyring->args.function_code = 0x07;
  } else if (request.getOperation() == "delete") {
    p_arg_area_keyring->args.function_code = 0x0A;
  }
  p_arg_area_keyring->args.attributes = 0;

  IRRSDL00::callIRRSDL00(&p_arg_area_keyring->args, &parmlist_version, nullptr);

  request.setSAFReturnCode(p_arg_area_keyring->args.SAF_rc);
  request.setRACFReturnCode(p_arg_area_keyring->args.RACF_rc);
  request.setRACFReasonCode(p_arg_area_keyring->args.RACF_rsn);
}

void IRRSDL00::addCertificate(SecurityRequest &request,
                              certificate_add_arg_area_t *p_arg_area_keyring) {
  uint32_t parmlist_version              = 0;

  p_arg_area_keyring->args.function_code = 0x08;
  if (request.getStatus() == "TRUST" || request.getStatus() == "trust") {
    p_arg_area_keyring->args.attributes = 0x80000000;
  } else if (request.getStatus() == "HIGHTRUST" ||
             request.getStatus() == "hightrust") {
    p_arg_area_keyring->args.attributes = 0x40000000;
  } else if (request.getStatus() == "NOTRUST" ||
             request.getStatus() == "notrust") {
    p_arg_area_keyring->args.attributes = 0x20000000;
  }

  auto result_unique_ptr =
      std::make_unique<char[]>(sizeof(certificate_add_parms_results_t));
  std::memset(result_unique_ptr.get(), 0,
              sizeof(certificate_add_parms_results_t));
  p_arg_area_keyring->p_result_buffer =
      reinterpret_cast<certificate_add_parms_results_t *>(
          result_unique_ptr.get());
  p_arg_area_keyring->p_result_buffer->result_buffer_length =
      sizeof(certificate_add_parms_results_t);
  request.setRawResultLength(
      p_arg_area_keyring->p_result_buffer->result_buffer_length);

  certificate_add_parms_results_t *p_result_buffer =
      p_arg_area_keyring->p_result_buffer;

  cddlx_put_cert_t *p_parm_put_cert =
      &p_result_buffer->result_buffer_add_certificate;

  if (request.getUsage() == "PERSONAL" || request.getUsage() == "personal") {
    *(reinterpret_cast<uint32_t *>(&p_parm_put_cert->cddlx_pcert_usage)) =
        0x00000008;
  } else if (request.getUsage() == "CERTAUTH" ||
             request.getUsage() == "certauth") {
    *(reinterpret_cast<uint32_t *>(&p_parm_put_cert->cddlx_pcert_usage)) =
        0x00000002;
  }

  if (request.getDefault() == "yes") {
    p_parm_put_cert->cddlx_pcert_default = 1;
  }

  std::string cert_file = request.getCertificateFile();
  if (cert_file != "") {
    readFile(cert_file, &p_parm_put_cert->cddlx_pcert_ptr,
             &p_parm_put_cert->cddlx_pcert_len);
  }

  std::string privkey_file = request.getPrivateKeyFile();
  if (privkey_file != "") {
    readFile(privkey_file, &p_parm_put_cert->cddlx_pkey_ptr,
             &p_parm_put_cert->cddlx_pkey_len);
  }

  auto cert_label_unique_ptr = std::make_unique<char[]>(LABEL_BUFFER_SIZE);
  char *p_cert_label         = cert_label_unique_ptr.get();
  std::memset(p_cert_label, 0, LABEL_BUFFER_SIZE);
  p_parm_put_cert->cddlx_plabel_len = request.getLabel().length();
  if (p_parm_put_cert->cddlx_plabel_len > 32)
    p_parm_put_cert->cddlx_plabel_len = 32;
  std::memcpy(p_cert_label, request.getLabel().c_str(),
              p_parm_put_cert->cddlx_plabel_len);
  __a2e_l(p_cert_label, p_parm_put_cert->cddlx_plabel_len);
  p_parm_put_cert->cddlx_plabel_ptr =
      reinterpret_cast<unsigned char *>(p_cert_label);

  std::string owner = request.getOwner();
  // Automatically convert lowercase userid to uppercase.
  std::transform(owner.begin(), owner.end(), owner.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  p_parm_put_cert->cddlx_pcert_userid[0] = owner.length();
  std::memcpy(&p_parm_put_cert->cddlx_pcert_userid[1], owner.c_str(),
              owner.length());
  __a2e_l(reinterpret_cast<char *>(&p_parm_put_cert->cddlx_pcert_userid[1]),
          owner.length());

  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_parm_put_cert),
                                sizeof(cddlx_put_cert_t));

  IRRSDL00::callIRRSDL00(&p_arg_area_keyring->args, &parmlist_version,
                         p_parm_put_cert);

  request.setSAFReturnCode(p_arg_area_keyring->args.SAF_rc);
  request.setRACFReturnCode(p_arg_area_keyring->args.RACF_rc);
  request.setRACFReasonCode(p_arg_area_keyring->args.RACF_rsn);

  if (p_parm_put_cert->cddlx_pkey_ptr != nullptr) {
    std::free(p_parm_put_cert->cddlx_pkey_ptr);
  }

  if (p_parm_put_cert->cddlx_pcert_ptr != nullptr) {
    std::free(p_parm_put_cert->cddlx_pcert_ptr);
  }
}

void IRRSDL00::deleteCertificate(
    SecurityRequest &request, certificate_delete_arg_area_t *p_arg_area_keyring,
    bool delete_from_keyring_only) {
  uint32_t parmlist_version              = 0;

  p_arg_area_keyring->args.function_code = 0x09;
  if (!delete_from_keyring_only) {
    p_arg_area_keyring->args.attributes = 0x80000000;
  } else {
    p_arg_area_keyring->args.attributes = 0;
  }

  auto result_unique_ptr =
      std::make_unique<char[]>(sizeof(certificate_delete_parms_results_t));
  std::memset(result_unique_ptr.get(), 0,
              sizeof(certificate_delete_parms_results_t));
  p_arg_area_keyring->p_result_buffer =
      reinterpret_cast<certificate_delete_parms_results_t *>(
          result_unique_ptr.get());
  p_arg_area_keyring->p_result_buffer->result_buffer_length =
      sizeof(certificate_delete_parms_results_t);
  request.setRawResultLength(
      p_arg_area_keyring->p_result_buffer->result_buffer_length);

  certificate_delete_parms_results_t *p_result_buffer =
      p_arg_area_keyring->p_result_buffer;

  cddlx_remove_cert_t *p_parm_remove_cert =
      &p_result_buffer->result_buffer_delete_certificate;

  auto cert_label_unique_ptr = std::make_unique<char[]>(LABEL_BUFFER_SIZE);
  char *p_cert_label         = cert_label_unique_ptr.get();
  std::memset(p_cert_label, 0, LABEL_BUFFER_SIZE);
  p_parm_remove_cert->cddlx_rlabel_len = request.getLabel().length();
  if (p_parm_remove_cert->cddlx_rlabel_len > 32)
    p_parm_remove_cert->cddlx_rlabel_len = 32;
  std::memcpy(p_cert_label, request.getLabel().c_str(),
              p_parm_remove_cert->cddlx_rlabel_len);
  __a2e_l(p_cert_label, p_parm_remove_cert->cddlx_rlabel_len);
  p_parm_remove_cert->cddlx_rlabel_ptr =
      reinterpret_cast<unsigned char *>(p_cert_label);

  p_parm_remove_cert->cddlx_rcert_userid[0] = request.getOwner().length();
  std::memcpy(&p_parm_remove_cert->cddlx_rcert_userid[1],
              request.getOwner().c_str(), request.getOwner().length());
  __a2e_l(reinterpret_cast<char *>(&p_parm_remove_cert->cddlx_rcert_userid[1]),
          request.getOwner().length());

  Logger::getInstance().hexDump(reinterpret_cast<char *>(p_parm_remove_cert),
                                sizeof(cddlx_remove_cert_t));

  IRRSDL00::callIRRSDL00(&p_arg_area_keyring->args, &parmlist_version,
                         p_parm_remove_cert);

  request.setSAFReturnCode(p_arg_area_keyring->args.SAF_rc);
  request.setRACFReturnCode(p_arg_area_keyring->args.RACF_rc);
  request.setRACFReasonCode(p_arg_area_keyring->args.RACF_rsn);
}

void IRRSDL00::readFile(const std::string &filename, void **p_p_data,
                        uint32_t *p_len) {
  unsigned char *p_data = nullptr;
  int data_length;

  // open file
  FILE *fp = fopen(filename.c_str(), "r");
  if (fp == nullptr) {
    throw SEARError(
        std::string("Unable to open file '" + filename + "' for reading."));
  }
  // get size of file
  fseek(fp, 0L, SEEK_END);
  data_length = ftell(fp);
  rewind(fp);
  // allocate space to read in data from file
  auto unique_p_data = std::make_unique<char[]>(data_length + 1);
  p_data             = reinterpret_cast<unsigned char *>(unique_p_data.get());
  if (p_data == nullptr) {
    fclose(fp);
    throw SEARError(std::string("Unable to allocate space for data in file."));
  }
  // read file data
  fread(p_data, data_length, 1, fp);
  fclose(fp);

  *p_p_data = p_data;
  *p_len    = data_length;

  if (*p_len < 5 ||
      std::strncmp(reinterpret_cast<char *>(p_data), "-----", 5)) {
    unique_p_data.release();
  } else {
    auto unique_p_b64 = std::make_unique<char[]>(data_length + 1);
    unsigned char *p_b64 =
        reinterpret_cast<unsigned char *>(unique_p_b64.get());

    unsigned char *p_data_work = p_data;
    unsigned char *p_b64_work  = p_b64;
    int idx_data_work          = 0;
    int len_b64_work           = 0;

    for (idx_data_work = 0;
         idx_data_work < *p_len && *p_data_work != 0x0D && *p_data_work != 0x0A;
         idx_data_work++) {
      p_data_work++;
    }

    for (; idx_data_work < *p_len && *p_data_work != '-'; idx_data_work++) {
      if (*p_data_work != 0x0A && *p_data_work != 0x0D) {
        *p_b64_work = *p_data_work;
        p_b64_work++;
        len_b64_work++;
      }
      p_data_work++;
    }

    *p_b64_work         = 0;

    auto unique_p_data2 = std::make_unique<char[]>(len_b64_work);
    unsigned char *p_data2 =
        reinterpret_cast<unsigned char *>(unique_p_data2.get());
    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    EVP_DecodeInit(ctx);
    int decode_len = 0;
    EVP_DecodeUpdate(ctx, p_data2, &decode_len, p_b64, len_b64_work);
    *p_len = decode_len;
    EVP_DecodeFinal(ctx, p_data2 + *p_len, &decode_len);
    *p_len += decode_len;
    EVP_ENCODE_CTX_free(ctx);
    p_data    = nullptr;
    *p_p_data = p_data2;

    unique_p_data2.release();
  }
}
}  // namespace SEAR
