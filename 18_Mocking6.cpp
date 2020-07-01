#include <gmock/gmock.h>

// C++에서 의존성 주입 모델
//  1) 명시적인 인터페이스를 통한 의존성 주입

struct Packet {};
struct PacketStream {
	virtual ~PacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0;
	virtual const Packet* GetPacket(size_t packet_number) const = 0;
};

class ConcreatPacketStream : public PacketStream {
public:
	void AppendPacket(Packet* new_packet) override {
		printf("ConcreatPacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const override {
		printf("ConcreatPacketStream::GetPacket\n");
		return nullptr;
	}
};

class PacketReader {
public:
	void ReadPackets(PacketStream* stream, size_t packet_num) {
		printf("PacketReader::ReadPackets\n");
		stream->AppendPacket(nullptr);
		stream->GetPacket(42);
	}
};

//-------------------------------------
class MockPacketStream : public PacketStream {
public:
	// virtual void AppendPacket(Packet* new_packet) = 0;
	// virtual const Packet* GetPacket(size_t packet_number) const = 0;

	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (override, const));
};

TEST(PacketReaderTest, ReadPacketsTest_withMock) {
	MockPacketStream stream;
	PacketReader reader;

	reader.ReadPackets(&stream, 42);
}


TEST(PacketReaderTest, ReadPacketsTest) {
	ConcreatPacketStream stream;
	PacketReader reader;

	reader.ReadPackets(&stream, 42);
}









//  2) 암묵적인 인터페이스를 통한 의존성 주입 - Template
