#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "kyk_utils.h"
#include "kyk_message.h"
#include "mu_unit.h"
#include "dbg.h"

char* test_kyk_build_btc_new_message_for_ping()
{
    ptl_payload* pld = NULL;
    ptl_message* msg = NULL;
    struct ptl_ping_entity* et = NULL;
    int res = -1;

    kyk_new_ping_entity(&et);
    res = kyk_build_new_ping_payload(&pld, et);
    check(res == 0, "Failed to test_kyk_build_btc_new_message_for_ping: kyk_new_ptl_payload failed");

    res = kyk_build_new_ptl_message(&msg, KYK_MSG_TYPE_PING, NT_MAGIC_MAIN, pld);
    mu_assert(res == 0, "Failed to test_kyk_build_btc_new_message_for_ping");

    /* kyk_print_ptl_message(msg); */

    return NULL;

error:

    return "Failed to test_kyk_build_btc_new_message_for_ping";
}


char* test_kyk_build_btc_new_message_for_pong()
{
    ptl_payload* pld = NULL;
    ptl_message* msg = NULL;
    uint64_t nonce = 123;
    int res = -1;

    res = kyk_build_new_pong_payload(&pld, nonce);
    check(res == 0, "Failed to test_kyk_build_btc_new_message_for_ping: kyk_new_ptl_payload failed");

    res = kyk_build_new_ptl_message(&msg, KYK_MSG_TYPE_PONG, NT_MAGIC_MAIN, pld);
    mu_assert(res == 0, "Failed to test_kyk_build_btc_new_message_for_pong");

    /* kyk_print_ptl_message(msg); */
    
    return NULL;

error:

    return "Failed to test_kyk_build_btc_new_message_for_ping";
}

char* test_kyk_build_new_ping_payload()
{
    ptl_payload* pld = NULL;
    struct ptl_ping_entity* et = NULL;     
    int res = -1;

    kyk_new_ping_entity(&et);
    res = kyk_build_new_ping_payload(&pld, et);
    mu_assert(res == 0, "Failed to test_kyk_build_new_ping_payload");
    mu_assert(pld -> len == 8, "Failed to test_kyk_build_new_ping_payload");
    /* printf("got nonce: %llu\n", et -> nonce); */

    kyk_free_ptl_payload(pld);
    free(et);
    
    return NULL;
}

char* test_kyk_new_seri_ver_entity_to_pld()
{
    ptl_payload* pld = NULL;
    ptl_ver_entity* ver = NULL;
    int32_t vers = 70014;
    const char* ip_src = LOCAL_IP_SRC;
    int port = 8333;
    uint64_t nonce = 0;
    const char* agent = "/BobWallet:0.0.0.1/";
    int32_t start_height = 0;
    int res = -1;

    res = kyk_build_new_version_entity(&ver, vers, ip_src, port, nonce, agent, strlen(agent), start_height);
    check(res == 0, "Failed to test_kyk_new_seri_ver_entity_to_pld: kyk_build_new_version_entity failed");

    res = kyk_new_seri_ver_entity_to_pld(ver, &pld);
    mu_assert(res == 0, "Failed to test_kyk_new_seri_ver_entity_to_pld");

    return NULL;

error:

    return "Failed to test_kyk_new_seri_ver_entity_to_pld";

}

char* test_kyk_build_new_getheaders_entity()
{
    ptl_gethder_entity* et = NULL;
    uint32_t version = 1;
    int res = -1;

    res = kyk_build_new_getheaders_entity(&et, version);
    mu_assert(res == 0, "Failed test_kyk_build_new_getheaders_entity");
    mu_assert(et, "Failed to kyk_build_new_getheaders_entity");

    return NULL;
}

char* test_kyk_new_seri_gethder_entity_to_pld()
{
    ptl_gethder_entity* et = NULL;
    ptl_payload* pld = NULL;
    uint32_t version = 1;
    int res = -1;

    res = kyk_build_new_getheaders_entity(&et, version);
    check(res == 0, "Failed to test_kyk_new_seri_gethder_entity_to_pld: kyk_build_new_getheaders_entity failed");

    res = kyk_new_seri_gethder_entity_to_pld(et, &pld);
    mu_assert(res == 0, "Failed to test_kyk_new_seri_gethder_entity_to_pld");

    return NULL;

error:

    return "Failed to test_kyk_new_seri_gethder_entity_to_pld";

}

char* test_kyk_seri_hd_chain_to_new_pld()
{
    ptl_payload* pld = NULL;
    struct kyk_blk_hd_chain* hd_chain = NULL;
    uint8_t buf[160] = {
	0x01, 0x00, 0x00, 0x00, 0x55, 0xbd, 0x84, 0x0a,
	0x78, 0x79, 0x8a, 0xd0, 0xda, 0x85, 0x3f, 0x68,
	0x97, 0x4f, 0x3d, 0x18, 0x3e, 0x2b, 0xd1, 0xdb,
	0x6a, 0x84, 0x2c, 0x1f, 0xee, 0xcf, 0x22, 0x2a,
	0x00, 0x00, 0x00, 0x00, 0xff, 0x10, 0x4c, 0xcb,
	0x05, 0x42, 0x1a, 0xb9, 0x3e, 0x63, 0xf8, 0xc3,
	0xce, 0x5c, 0x2c, 0x2e, 0x9d, 0xbb, 0x37, 0xde,
	0x27, 0x64, 0xb3, 0xa3, 0x17, 0x5c, 0x81, 0x66,
	0x56, 0x2c, 0xac, 0x7d, 0x51, 0xb9, 0x6a, 0x49,
	0xff, 0xff, 0x00, 0x1d, 0x28, 0x3e, 0x9e, 0x70,
	0x01, 0x00, 0x00, 0x00, 0xee, 0xa2, 0xd4, 0x8d,
	0x2f, 0xce, 0xd4, 0x34, 0x68, 0x42, 0x83, 0x5c,
	0x65, 0x9e, 0x49, 0x3d, 0x32, 0x3f, 0x06, 0xd4,
	0x03, 0x44, 0x69, 0xa8, 0x90, 0x57, 0x14, 0xd1,
	0x00, 0x00, 0x00, 0x00, 0xf2, 0x93, 0xc8, 0x69,
	0x73, 0xe7, 0x58, 0xcc, 0xd1, 0x19, 0x75, 0xfa,
	0x46, 0x4d, 0x4c, 0x3e, 0x85, 0x00, 0x97, 0x9c,
	0x95, 0x42, 0x5c, 0x7b, 0xe6, 0xf0, 0xa6, 0x53,
	0x14, 0xd2, 0xf2, 0xd5, 0xc9, 0xba, 0x6a, 0x49,
	0xff, 0xff, 0x00, 0x1d, 0x07, 0xa8, 0xf2, 0x26,
    };
    int res = -1;
    
    res = kyk_deseri_blk_hd_chain(&hd_chain, buf, sizeof(buf));
    check(res == 0, "Failed to test_kyk_seri_hd_chain_to_new_pld: kyk_deseri_blk_hd_chain failed");
    res = kyk_seri_hd_chain_to_new_pld(&pld, hd_chain);
    mu_assert(res == 0, "Failed to test_kyk_seri_hd_chain_to_new_pld");

    return NULL;

error:

    return "Failed to test_kyk_seri_hd_chain_to_new_pld";
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_kyk_build_btc_new_message_for_ping);
    mu_run_test(test_kyk_build_btc_new_message_for_pong);
    mu_run_test(test_kyk_build_new_ping_payload);
    mu_run_test(test_kyk_new_seri_ver_entity_to_pld);
    mu_run_test(test_kyk_build_new_getheaders_entity);
    mu_run_test(test_kyk_new_seri_gethder_entity_to_pld);
    mu_run_test(test_kyk_seri_hd_chain_to_new_pld);
    
    return NULL;
}

MU_RUN_TESTS(all_tests);