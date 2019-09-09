prog=$1;
if [[ ! -x $prog ]]; then
    echo "Wrong file path"
    exit 1
fi

for test_file in `ls tests/*.t`; do
    echo "Execute ${test_file}"
    if ! $prog < ./$test_file > tmp; then
        echo "ERROR"
        continue
    fi
    answer_file="${test_file%.*}.a"

    if ! diff --suppress-common-lines -y "${answer_file}" tmp; then
        tput setaf 1; echo "Failed"
    else
        tput setaf 2; echo "OK"
    fi 
    tput sgr0
done

