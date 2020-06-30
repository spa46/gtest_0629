#include <gmock/gmock.h>
// C++ 에서는 인터페이스 기반 프로그래밍 방식
// 1) 인터페이스를 명시적으로 구현하는 방법. - X

#if 0
struct IPacketStream {
	virtual ~IPacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0
	virtual const Packet* GetPacket(size_t packet_number) const  = 0;
};

class ConcreatPacketStream : public IPacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatPacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {}
};


class PacketReader {
public:
	void ReadPacket(IPacketStream* stream, size_t packet_num) {
		stream->AppendPacket(nullptr);
	}
};
#endif

// 2) Template을 통해 암묵적으로 약속하는 방법.
//---------------
struct Packet {};

class ConcreatPacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatPacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {}
};

template <typename PacketStream> 
class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		stream->AppendPacket(nullptr);
	}
};

class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(PacketTest, Sample) {
	// 제품 코드에서 사용하는 방식
	ConcreatPacketStream stream;
	PacketReader<ConcreatPacketStream> reader;

	reader.ReadPacket(&stream, 42);
}

TEST(PacketTest, Sample2) {
	// 테스트 코드에서 모의 객체를 적용하는 방법
	MockPacketStream mock;
	PacketReader<MockPacketStream> reader;

	reader.ReadPacket(&mock, 42);
}









