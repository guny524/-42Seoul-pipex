git clone https://github.com/gmarcha/pipexMedic.git
cd pipexMedic
# 클러스터에서 실행하면 bash 경로가 bin/bash인데
# 테스터가 리눅스 기반이라 usr/bin/bash로 되어있어서 실행 안되는 거임
# 리눅스에서 돌리는 사람은 sed 명령어 부분만 지워주면 됨
sed -i tmp 's/\/usr\/bin\/bash/\/bin\/bash/g' src/test.c
rm src/test.ctmp
bash test.sh m
# bash test.sh a
cd ..
make fclean

git clone https://github.com/mariadaan/PIPEXaminator.git
make
cd PIPEXaminator
bash all_tests.sh
cd ..
make fclean

git clone https://github.com/vfurmane/pipex-tester.git
cd pipex-tester
./run.sh
cd ..
make fclean

git clone https://github.com/ael-bekk/PIPEX_TESTER.git
cd PIPEX_TESTER
chmod +x tester.sh
./tester.sh -pe
# ./tester.sh -a
cd ..
make fclean

git clone https://github.com/Yoo0lh/pipex_tester_42.git
cd pipex_tester_42
./pipex_tester.sh m
# ./pipex_tester.sh a
cd ..

echo "\033[32;1m"FINISHED enter will remove testers and diff results, ctrl + c to check remain"\033[m"
read $a
rm -rf pipexMedic PIPEXaminator pipex-tester PIPEX_TESTER pipex_tester_42
