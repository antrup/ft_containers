#!/bin/bash

echo "#####   VECTOR   ######"
echo ""
echo "Compiling vector tests"
make -s -C containers_tester ft_vector
make -s -C containers_tester std_vector
echo "Running vector tests"
echo ""
DIFF=$(diff <(containers_tester/ft_vector 2>&1) <(containers_tester/std_vector 2>&1))
if [ "$DIFF" == "" ] 
then
    echo  -e "\e[1mNo diff - SUCCESS\e[0m"
else
    echo "Diff detected - Failed"
fi
echo ""
echo "## VECTOR - SPEED TEST ##"
echo ""
echo "ft::vector:"
time (./containers_tester/ft_vector >log_ft_vect 2>&1)
echo ""
echo "std::vector:"
time (./containers_tester/std_vector >log_std_vect 2>&1)
echo ""
echo "#####   MAP   ######"
echo ""
echo "Compiling map tests"
make -s -C containers_tester ft_map
make -s -C containers_tester std_map
echo "Running map tests"
echo ""
DIFF=$(diff <(containers_tester/ft_map 2>&1) <(containers_tester/std_map 2>&1))
if [ "$DIFF" == "" ] 
then
    echo  -e "\e[1mNo diff - SUCCESS\e[0m"
else
    echo "Diff detected - Failed"
fi
echo ""
echo "## MAP - SPEED TEST ##"
echo ""
echo "ft::map:"
time (./containers_tester/ft_map >log_ft_map 2>&1)
echo ""
echo "std::map:"
time (./containers_tester/std_map >log_std_map 2>&1)
echo ""
echo "#####   STACK   ######"
echo ""
echo "Compiling stack tests"
make -s -C containers_tester ft_stack
make -s -C containers_tester std_stack
echo "Running stack tests"
echo ""
DIFF=$(diff <(containers_tester/ft_stack 2>&1) <(containers_tester/std_stack 2>&1))
if [ "$DIFF" == "" ] 
then
    echo  -e "\e[1mNo diff - SUCCESS\e[0m"
else
    echo "Diff detected - Failed"
fi
echo ""
echo "## STACK - SPEED TEST ##"
echo ""
echo "ft::stack:"
time (./containers_tester/ft_stack >log_ft_stack 2>&1)
echo ""
echo "std::stack:"
time (./containers_tester/std_stack >log_std_stack 2>&1)
echo ""
echo "#####   SET   ######"
echo ""
echo "Compiling set tests"
make -s -C containers_tester ft_set
make -s -C containers_tester std_set
echo "Running set tests"
echo ""
DIFF=$(diff <(containers_tester/ft_set 2>&1) <(containers_tester/std_set 2>&1))
if [ "$DIFF" == "" ] 
then
    echo  -e "\e[1mNo diff - SUCCESS\e[0m"
else
    echo "Diff detected - Failed"
fi
echo ""
echo "## SET - SPEED TEST ##"
echo ""
echo "ft::set:"
time (./containers_tester/ft_set >log_ft_set 2>&1)
echo ""
echo "std::set:"
time (./containers_tester/std_set >log_std_set 2>&1)

