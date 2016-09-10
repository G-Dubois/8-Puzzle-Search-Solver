echo "No Heuristic"
cat test-input.txt | a-star.exe 0
echo "Displaced Tiles"
cat test-input.txt | a-star.exe 1
echo "Manhattan"
cat test-input.txt | a-star.exe 2
echo "My Heuristic"
cat test-input.txt | a-star.exe 3
