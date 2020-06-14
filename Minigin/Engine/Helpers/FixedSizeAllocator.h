#pragma once
#include <vector>

namespace MyEngine
{
	class FixedSizeAllocator
	{
	public:
		FixedSizeAllocator(const FixedSizeAllocator& other) = delete;
		FixedSizeAllocator(FixedSizeAllocator&& other) noexcept = delete;
		FixedSizeAllocator& operator=(const FixedSizeAllocator& other) = delete;
		FixedSizeAllocator& operator=(FixedSizeAllocator&& other) noexcept = delete;

		explicit FixedSizeAllocator(int size, size_t blockSize);
		~FixedSizeAllocator();

		void* Acquire();

		void Release(void* release);
		
		void Reset();

		size_t GetFreeSpaceAmount() const;
		size_t GetUsedSpaceAmount() const;

		std::vector<char*> GetUsedSpots() const;

	private:
		std::vector<char*> m_pMemoryPool;
		std::vector<bool> m_IsUsed;
		const size_t m_BlockSize;
	};
}
