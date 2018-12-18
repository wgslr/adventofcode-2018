for i in (seq 1000 1100); printf "%8d %s\n" $i (./code $i < input  | head -n 1); end

