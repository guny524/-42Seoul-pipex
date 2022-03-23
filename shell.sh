echo "\033[32;1m"pipexMedic"\033[m"
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
# 그리고 이 테스터기에서 멘데토리 3번째가 다르게 나오는 것을 볼 수 있는데
# main.c에 "grep Hello", "ls -la src/"요 부분
# "grep Hello", "ls -la" 로 바꿔주면 outputPipex의 용량이 다른 걸 볼 수 있다.
# 이거 테스터에서 pipex 실행하고, bash 실행하고 나중에 unlink해서 그런 거임
#
# 그리고 에러 핸들링 2번 env에 NULL넣어서 pipex를 실행하는데
# 테스터의 의도는 환경변수가 NULL이여도 default path를 가지고 있다가 실행하라는 것 같은데
# 이건 구현하기 나름인 듯
#
# 그리고 에러 메세지가 bash랑 조금만 달라도 틀렸다고 함

echo "\033[32;1m"PIPEXaminator"\033[m"
git clone https://github.com/mariadaan/PIPEXaminator.git
make
cd PIPEXaminator
bash all_tests.sh
cd ..
make fclean
# 이 테스터에서도 argument 갯수 다르게 주는데
# 이건 어떤 걸 만들기로 했냐에 따라 달라진다 생각함
# minishell을 하는 거면 파이프 파싱까지 하는게 맞는데
# 과제에선 format을 정해줬음
# < test.txt | > res.txt 이거 zsh에서는 되는데 bash에서는 안 됨
# 그럼 어디에 맞춰야 함? 정해진 게 없음, 정하기 나름임

echo "\033[32;1m"pipex-tester"\033[m"
git clone https://github.com/vfurmane/pipex-tester.git
cd pipex-tester
./run.sh
cd ..
make fclean

echo "\033[32;1m"PIPEX_TESTER"\033[m"
git clone https://github.com/ael-bekk/PIPEX_TESTER.git
cd PIPEX_TESTER
chmod +xrw tester.sh
sed -i tmp 's/  kill -9 $i/echo finish/g' tester.sh
rm src/test.ctmp
./tester.sh -pe
# ./tester.sh -a
cd ..
make fclean

echo "\033[32;1m"pipex_tester_42"\033[m"
git clone https://github.com/Yoo0lh/pipex_tester_42.git
cd pipex_tester_42
./pipex_tester.sh m
# ./pipex_tester.sh a
cd ..
make fclean

echo "\033[32;1m"FINISHED enter will remove testers and diff results, ctrl + c to check remain"\033[m"
read $a
rm -rf pipexMedic PIPEXaminator pipex-tester PIPEX_TESTER pipex_tester_42
