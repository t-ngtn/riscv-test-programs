
# Baremetal versions (for gem5)
hello:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/hello/src/hello_baremetal.c -o tests/hello/bin/hello'

matrix_multiply:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/matrix_multiply/src/matrix_multiply_baremetal.c -o tests/matrix_multiply/bin/matrix_multiply'

matrix_multiply_short:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/matrix_multiply/src/matrix_multiply_short_baremetal.c -o tests/matrix_multiply/bin/matrix_multiply_short'

array_shuffle:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/array_shuffle/src/array_shuffle_baremetal.c -o tests/array_shuffle/bin/array_shuffle'

memory_copy:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/memory_copy/src/memory_copy_baremetal.c -o tests/memory_copy/bin/memory_copy'

memory_copy_short:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/memory_copy/src/memory_copy_short_baremetal.c -o tests/memory_copy/bin/memory_copy_short'

linked_list:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/linked_list/src/linked_list_baremetal.c -o tests/linked_list/bin/linked_list'

cache_stress:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/cache_stress/src/cache_stress_baremetal.c -o tests/cache_stress/bin/cache_stress'

# Standard C versions (with libc)
hello_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/hello/src/hello.c -o tests/hello/bin/hello_std'

matrix_multiply_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/matrix_multiply/src/matrix_multiply.c -o tests/matrix_multiply/bin/matrix_multiply_std'

matrix_multiply_short_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/matrix_multiply/src/matrix_multiply_short.c -o tests/matrix_multiply/bin/matrix_multiply_short_std'

array_shuffle_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/array_shuffle/src/array_shuffle.c -o tests/array_shuffle/bin/array_shuffle_std'

memory_copy_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/memory_copy/src/memory_copy.c -o tests/memory_copy/bin/memory_copy_std'

memory_copy_short_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/memory_copy/src/memory_copy_short.c -o tests/memory_copy/bin/memory_copy_short_std'

linked_list_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/linked_list/src/linked_list.c -o tests/linked_list/bin/linked_list_std'

cache_stress_std:
	./dockcross-linux-riscv64 bash -c '$$CC tests/cache_stress/src/cache_stress.c -o tests/cache_stress/bin/cache_stress_std'

# Build all baremetal versions
all: hello matrix_multiply matrix_multiply_short array_shuffle memory_copy memory_copy_short linked_list cache_stress

# Build all standard versions
all_std: hello_std matrix_multiply_std matrix_multiply_short_std array_shuffle_std memory_copy_std memory_copy_short_std linked_list_std cache_stress_std

# Clean
clean:
	rm -f tests/*/bin/*

# Legacy targets (kept for compatibility)
memory:
	./dockcross-linux-riscv64 bash -c '$$CC -static -nostdlib -ffreestanding tests/memory_test/src/memory_test_baremetal.c -o tests/memory_test/bin/memory_test'

scp:
	scp tests/hello/bin/hello nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/
	scp tests/matrix_multiply/bin/matrix_multiply nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/
	scp tests/array_shuffle/bin/array_shuffle nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/
	scp tests/memory_copy/bin/memory_copy nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/
	scp tests/linked_list/bin/linked_list nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/
	scp tests/cache_stress/bin/cache_stress nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/

scp_all:
	scp tests/*/bin/* nagatani@cad005:/home/nagatani/gem5/riscv-test-programs/