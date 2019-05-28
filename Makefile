CC=g++-9 -O3 -std=c++17
CFLAGS=-I./include
LIBS=-ltbb

build:
	mkdir build && $(CC) -o build/short src/short.cpp $(CFLAGS) $(LIBS)

generate-tests:
	@echo "Generating sample data for testing..."
	python3 scripts/generate/tests.py

generate-cutoff-data:
	@echo "Generating cutoff data..."
	python3 scripts/generate/cutoff_data.py

generate-perf-data:
	@echo "Generating performance data..."
	python3 scripts/generate/perf_data.py

test-small:
	@echo "Testing for small vectors..."
	python3 scripts/test/cness.py s

test-medium:
	@echo "Testing for medium vectors..."
	python3 scripts/test/cness.py m

test-large:
	@echo "Testing for large vectors..."
	python3 scripts/test/cness.py l

test-trivial:
	python3 scripts/test/trivial.py

perf-small:
	@echo "Testing performance for small vectors..."
	python3 scripts/test/perf.py s

perf-medium:
	@echo "Testing performance for medium vectors..."
	python3 scripts/test/perf.py m

perf-large:
	@echo "Testing performance for large vectors..."
	python3 scripts/test/perf.py l

analyze-cutoff-data:
	python3 scripts/analyze/cutoff_data.py

analyze-perf-data:
	python3 scripts/analyze/perf_data.py

test-correctness: build generate-tests test-small test-medium test-large test-trivial

test-performance: build generate-tests perf-small perf-medium perf-large

analyze: build generate-tests generate-cutoff-data generate-perf-data analyze-cutoff-data analyze-perf-data

clean:
	rm -rf build results resources/*/
