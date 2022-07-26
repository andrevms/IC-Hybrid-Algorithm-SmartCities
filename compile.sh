#!/bin/bash
cmake -S src/ -B out/ && cmake --build out/ --target clean && make -C out && ./out/IC-HYBRID-ALGORITHM-SMARTCITIES src/instancias/instancias10-10-3/TIC04-10-10-3.in