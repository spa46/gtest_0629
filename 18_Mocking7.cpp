#include <gmock/gmock.h>

// C++ - Template 이용한 의존성 주입
//      : 단위 전략(Policy Based Design)
//        - Modern C++ Design

// 핵심: Template을 통한 의존 객체 전달
//       함수가 명시적인 인터페이스가 아니라 암묵적으로 약속한다.

struct Packet {};
class ConcreatPacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatPacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatPacketStream::GetPacket\n");
		return nullptr;
	}
};

template <typename PacketStream>
class PacketReader {
public:
	void ReadPackets(PacketStream* stream, size_t packet_num) {
		printf("PacketReader::ReadPackets\n");
		stream->AppendPacket(nullptr);
		stream->GetPacket(42);
	}
};

//-------------------------------------

// 클래스 템플릿은 타입 추론이 불가능하다.
// 템플릿 함수는 타입 추론이 가능하다.
//  => 객체를 생성하는 템플릿 함수를 만들면, 암시적 추론이 가능하기 때문에
//     편리하다.

class MockPacketStream {
public:
	// void AppendPacket(Packet* new_packet);
	// const Packet* GetPacket(size_t packet_number) const;

	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

template <typename T>
PacketReader<T>* CreatePacketReader(const T& ref) {
	return new PacketReader<T>();
}


TEST(PacketReaderTest, ReadPacketsTest_withMock) {
	MockPacketStream stream;

	auto reader = CreatePacketReader(stream);

	// PacketReader<MockPacketStream> reader;
	// reader.ReadPackets(&stream, 42);
}


TEST(PacketReaderTest, ReadPacketsTest) {
	ConcreatPacketStream stream;
	PacketReader<ConcreatPacketStream> reader;

	reader.ReadPackets(&stream, 42);
}







#if 0
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
TEST(PacketReaderTest, ReadPacketsTest) {
	ConcreatPacketStream stream;
	PacketReader reader;

	reader.ReadPackets(&stream, 42);
}

#endif









//  2) 암묵적인 인터페이스를 통한 의존성 주입 - Template
