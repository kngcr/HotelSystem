echo "Running tests..."
echo

echo "*****"
echo -e "Hotel Management System...\\n"
echo "*****"
echo -e "Room details\\n"

output_room=$(./hotel < test/input_room.txt)
echo "$output_room"

if [ $? -eq 0 ] ; then
  echo -e "\\nPass: Program exited zero"
else
  echo "Fail: Program did not exit zero"
  exit 1
fi

exp_avl_rooms_after="Room Number: 	242
Room with AC/No AC (A/N): A
Type of Comfort (S/N): N
Room Size (B/S): S
Daily Rate: 250"

if [[ ${output_room//[[:space:]]/} == *${exp_avl_rooms_after//[[:space:]]/}* ]] ; then
  echo -e "Pass: Room management is correct"
else
  echo "Expected '$exp_avl_rooms_after' but got: $output_room"
  exit 1
fi

echo "*****"
echo -e "Check-in & check-out\\n"

output_check_in_out=$(./hotel < test/input_check_in_out.txt)
echo "$output_check_in_out"

if [ $? -eq 0 ] ; then
  echo -e "\\nPass: Program exited zero"
else
  echo "Fail: Program did not exit zero"
  exit 1
fi

exp_checkout_details="Customer Name : Roo
Room Number : 121
Address : Honolulu
Phone : 987654321
Total Amount Due : 1600 /
Advance Paid: 200 /
*** Total Payable: 1400/ only"

if [[ ${output_check_in_out//[[:space:]]/} == *${exp_checkout_details//[[:space:]]/}* ]] ; then
  echo -e "Pass: Checkout summary is correct"
else
  echo "Expected '$exp_checkout' but got: $output_check_in_out"
  exit 1
fi


echo "*****"
echo -e "Guest summary\\n"

output_guest_summary=$(./hotel < test/input_guest_summary.txt)
echo "$output_guest_summary"

if [ $? -eq 0 ] ; then
  echo -e "\\nPass: Program exited zero"
else
  echo "Fail: Program did not exit zero"
  exit 1
fi

exp_guest_summary1="Customer First Name : Roo
 Room Number : 121
 Address (city only) : Honolulu
 Phone : 987654321"

exp_guest_sumarry2="Customer First Name : Sulu
 Room Number : 242
 Address (city only) : Honolulu
 Phone : 987654321"

if [[ ${output_guest_summary//[[:space:]]/} == *${exp_guest_summary1//[[:space:]]/}* && 
      ${output_guest_summary//[[:space:]]/} == *${exp_guest_summary2//[[:space:]]/}* ]] ; then
  echo -e "Pass: Guest summary is correct"
else
  echo "Expected '$exp_guest_summary' and '$exp_guest_summary2' but got: $output_guest_summary"
  exit 1
fi

# exp_cust="Customer Name: Roo 
# Room Number: 121"

# if [[ ${output_hotel//[[:space:]]/} == *${exp_cust//[[:space:]]/}* ]] ; then
#   echo -e "Pass: Customer search is correct"
# else
#   echo "Expected '$exp_cust' but got: $output_hotel"
#   exit 1
# fi

echo
echo "*****"
echo
echo "All tests passed."

exit 0
