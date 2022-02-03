set -e
g++ -o gen generate.cpp
g++ -o a A.cpp
for((i = 1; i <= 20; ++i)); do
    ./gen $i > input_file$i.txt
    ./a < input_file$i.txt > output_file$i.txt
done