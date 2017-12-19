#ifndef KYK_VALIDATE_H__
#define KYK_VALIDATE_H__

struct kyk_blk_hd_chain;
struct kyk_blk_header;
struct kyk_block;
struct kyk_txin;
struct kyk_tx;

int kyk_validate_blk_header(const struct kyk_blk_hd_chain* hd_chain,
			    const struct kyk_blk_header* outHd);

int kyk_validate_block(const struct kyk_blk_hd_chain* hd_chain,
		       const struct kyk_block* blk);

int kyk_validate_txin_script_sig(const struct kyk_txin* txin,
				 const uint8_t* unsig_buf,
				 size_t unsig_buf_len,
				 const struct kyk_tx* prev_tx);


#endif
