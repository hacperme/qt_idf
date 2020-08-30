cmake_minimum_required(VERSION 3.5)

project(iotkit_sdk LANGUAGES C)


set(iotkit_sdk_sources
    certs/root_ca.c

    extension/state_desc.c

#    src/atm/at_api.c
#    src/atm/at_conn_mbox.c
#    src/atm/at_conn_mgmt.c
#    src/atm/at_mqtt.c
#    src/atm/at_parser.c
#    src/atm/at_ssl.c
#    src/atm/at_tcp.c

    src/dev_sign/dev_sign_mqtt.c

    src/coap/client/Cloud_CoAPExport.c
    src/coap/client/Cloud_CoAPMessage.c
    src/coap/client/Cloud_CoAPNetwork.c
    src/coap/client/iotx_coap_api.c
    src/coap/CoAPPacket/CoAPDeserialize_common.c
    src/coap/CoAPPacket/CoAPMessage_common.c
    src/coap/CoAPPacket/CoAPSerialize_common.c
    src/coap/server/CoAPExport.c
    src/coap/server/CoAPMessage.c
    src/coap/server/CoAPNetwork.c
    src/coap/server/CoAPObserve.c
    src/coap/server/CoAPPlatform.c
    src/coap/server/CoAPResource.c
    src/coap/server/CoAPServer.c

#    src/dev_bind/bind.c
#    src/dev_bind/bind_coap.c
#    src/dev_bind/bind_mqtt.c
#    src/dev_bind/bind_msg.c
#    src/dev_bind/bind_token.c
#    src/dev_bind/bind_utils.c

    src/dev_model/dm_api.c
    src/dev_model/dm_cota.c
    src/dev_model/dm_fota.c
    src/dev_model/dm_fota.h
    src/dev_model/dm_ipc.c
    src/dev_model/dm_log_report.c
    src/dev_model/dm_manager.c
    src/dev_model/dm_message.c
    src/dev_model/dm_message_cache.c
    src/dev_model/dm_msg_process.c
    src/dev_model/dm_opt.c
    src/dev_model/dm_ota.c
    src/dev_model/dm_shadow.c
    src/dev_model/dm_tsl_alink.c
    src/dev_model/dm_utils.c
    src/dev_model/impl_linkkit.c
    src/dev_model/iotx_cm.c
    src/dev_model/iotx_cm_coap.c
    src/dev_model/iotx_cm_mqtt.c
    src/dev_model/alcs/alcs_adapter.c
    src/dev_model/alcs/alcs_api.c
    src/dev_model/alcs/alcs_base64.c
    src/dev_model/alcs/alcs_client.c
    src/dev_model/alcs/alcs_coap.c
    src/dev_model/alcs/alcs_localsetup.c
    src/dev_model/alcs/alcs_mqtt.c
    src/dev_model/alcs/alcs_server.c
    src/dev_model/client/dm_client.c
    src/dev_model/client/dm_client_adapter.c
    src/dev_model/deprecated/impl_gateway.c
    src/dev_model/deprecated/impl_ntp.c
    src/dev_model/deprecated/impl_solo.c
    src/dev_model/server/dm_server.c
    src/dev_model/server/dm_server_adapter.c

    src/dev_reset/dev_reset.c

    src/dynamic_register/dynreg.c

    src/http/iotx_http_api.c

#    src/http2/http2_api.c
#    src/http2/http2_upload_api.c
#    src/http2/iotx_http2.c

    src/infra/infra_aes.c
    src/infra/infra_cjson.c
    src/infra/infra_compat.c
    src/infra/infra_defs.c
    src/infra/infra_httpc.c
    src/infra/infra_json_parser.c
    src/infra/infra_list.h
    src/infra/infra_log.c
    src/infra/infra_md5.c
    src/infra/infra_mem_stats.c
    src/infra/infra_net.c
    src/infra/infra_preauth.c
    src/infra/infra_prt_nwk_payload.c
    src/infra/infra_report.c
    src/infra/infra_sha1.c
    src/infra/infra_sha256.c
    src/infra/infra_string.c
    src/infra/infra_timer.c

    src/mqtt/mqtt_api.c
    src/mqtt/impl/iotx_mqtt_client.c
    src/mqtt/impl/MQTTConnectClient.c
    src/mqtt/impl/MQTTDeserializePublish.c
    src/mqtt/impl/MQTTPacket.c
    src/mqtt/impl/MQTTSerializePublish.c
    src/mqtt/impl/MQTTSubscribeClient.c
    src/mqtt/impl/MQTTUnsubscribeClient.c

    src/ota/iotx_ota.c
    src/ota/ota_coap.c
    src/ota/ota_fetch.c
    src/ota/ota_lib.c
    src/ota/ota_mqtt.c

    src/wifi_provision/connectivity/wifi_coap.c
    src/wifi_provision/connectivity/wifi_mqtt.c
    src/wifi_provision/dev_ap/awss_dev_ap.c
    src/wifi_provision/frameworks/awss.c
    src/wifi_provision/frameworks/awss_discover.c
    src/wifi_provision/frameworks/awss_main.c
    src/wifi_provision/frameworks/connect_ap.c
    src/wifi_provision/frameworks/zconfig_protocol.c
    src/wifi_provision/frameworks/zconfig_vendor_common.c
    src/wifi_provision/frameworks/aplist/awss_aplist.c
    src/wifi_provision/frameworks/ieee80211/zconfig_ieee80211.c
    src/wifi_provision/frameworks/utils/awss_crypt.c
    src/wifi_provision/frameworks/utils/awss_event.c
    src/wifi_provision/frameworks/utils/os_misc.c
    src/wifi_provision/frameworks/utils/passwd.c
    src/wifi_provision/frameworks/utils/zconfig_utils.c
    src/wifi_provision/ht40/awss_ht40.c
    src/wifi_provision/mcast_smartconfig/mcast_smartconfig.c
    src/wifi_provision/p2p/awss_wps.c
    src/wifi_provision/phone_ap/awss_aha.c
    src/wifi_provision/phone_ap/awss_wifimgr.c
    src/wifi_provision/smartconfig/awss_smartconfig.c
    src/wifi_provision/zero_config/awss_enrollee.c
    src/wifi_provision/zero_config/awss_registrar.c
   )





add_library(iotkit_sdk STATIC ${iotkit_sdk_sources})

target_link_libraries(iotkit_sdk iotkit_wrappers cJSON)

target_include_directories(iotkit_sdk PRIVATE
    ${EXTERNAL_DIR}/iotkit-embedded/src/infra
    ${EXTERNAL_DIR}/iotkit-embedded/wrappers
    ${EXTERNAL_DIR}/iotkit-embedded/src/mqtt
    ${EXTERNAL_DIR}/iotkit-embedded/src/atm
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap/client
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap/server
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap/CoAPPacket
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_bind
    ${EXTERNAL_DIR}/iotkit-embedded/src/http
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_model
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_model/client
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_sign
    ${EXTERNAL_DIR}/iotkit-embedded/src/dynamic_register
    ${EXTERNAL_DIR}/iotkit-embedded/src/http
    ${EXTERNAL_DIR}/iotkit-embedded/src/http2
    ${EXTERNAL_DIR}/iotkit-embedded/src/ota
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/connectivity
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/dev_ap
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks/aplist
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks/ieee80211
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks/utils
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/ht40
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/mcast_smartconfig
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/p2p
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/phone_ap
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/smartconfig
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/zero_config

)


