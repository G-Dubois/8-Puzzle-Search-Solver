for i in {0..3}; do
    echo "Using Heuristic $i"
    for j in {1..100}; do
        echo "Run #: $j"
        cat OLA1-input.txt | random_board.exe $j 100 | a-star.exe $i > results/results_h${i}_${j}.txt
    done
done
