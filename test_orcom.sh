#!/bin/bash



#global parameters
fastq_input=$1
fastq_output="out.fastq"
temp_output="temp"
orcom_folder="../bin"

echo -e "running run_orcon.sh scripts.....\n"
./run_orcom.sh $orcom_folder $fastq_input $temp_output

FILENAME1="./temp.cdna"
FILESIZE1=$(stat -c%s "$FILENAME1")
echo -e "\nSize of $FILENAME1 = $FILESIZE1 bytes.\n"

FILENAME2="./temp.cmeta"
FILESIZE2=$(stat -c%s "$FILENAME2")
echo -e "Size of $FILENAME2 = $FILESIZE2 bytes.\n"

compress_size=$(( $FILESIZE2 + $FILESIZE1 ))
echo -e "overall size of the compress data is $compress_size bytes.\n"

echo "running orcom_to_fastq.sh scripts....."
./orcom_to_fastq.sh $orcom_folder $temp_output $fastq_output


#comparing the original file and decompressed file  

./extract_dna_from_fastq.sh $fastq_input in_dna.txt

./extract_dna_from_fastq.sh $fastq_output out_dna.txt


cat in_dna.txt | sort >> file1

cat out_dna.txt | sort >> file2

echo -e '\nThe results are...\n'
if cmp -s "file1" "file2"; then
    printf 'The file "%s" is the same as "%s"\n' "input.dna" "output.dna"
else
    printf 'The file "%s" is different from "%s"\n' "input.dna" "output.dna"
fi




#diff in_dna.txt_sort out_dna.txt_sort