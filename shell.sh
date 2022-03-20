# git clone https://github.com/gmarcha/pipexMedic.git
# cd pipexMedic
# bash test.sh m
# # bash test.sh a

git clone https://github.com/mariadaan/PIPEXaminator.git
make
cd PIPEXaminator
bash all_tests.sh
cd ..
make fclean

git clone https://github.com/vfurmane/pipex-tester.git


echo -e "\033[32;1m"FINISHED enter will remove testers and diff results, ctrl + c to check remain"\033[m"
read $a
rm -rf pipexMedic PIPEXaminator
