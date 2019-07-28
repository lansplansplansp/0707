#define TEXT_SZ 2048//申请共享内存大小
struct shared_use_st
{
	int written_by_you;//IPC不提供同步机制，定义同步标志
	char some_text[TEXT_SZ];//共享内存
};