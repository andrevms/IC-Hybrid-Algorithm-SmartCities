#!/bin/bash
cmake -S src/ -B out/ && cmake --build out/ --target clean && make -C out && ./out/IC-HYBRID-ALGORITHM-SMARTCITIES src/instancias/instancias10-10-3/TIC01-10-10-3.in out/TIC01-10-10-3 src/instancias/instancias10-10-3/TIC02-10-10-3.in out/TIC02-10-10-3 src/instancias/instancias10-10-3/TIC03-10-10-3.in out/TIC03-10-10-3 src/instancias/instancias10-10-3/TIC04-10-10-3.in out/TIC04-10-10-3 
