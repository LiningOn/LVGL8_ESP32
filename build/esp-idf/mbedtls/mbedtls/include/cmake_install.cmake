# Install script for directory: F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/LVGL8_ESP32")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aesni.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/arc4.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/blowfish.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bn_mul.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/certs.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher_internal.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-1.3.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp_internal.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy_poll.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/havege.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md2.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md4.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md_internal.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/padlock.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk_internal.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs11.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa_internal.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_internal.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    "F:/ESP32/ESP-VS-IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/xtea.h"
    )
endif()

