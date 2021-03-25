int main()
{
   int i, x;
   char str[100];

   cout << "Please enter a string:\t";
   cin >> str;

   cout << "\nPlease choose following options: \n";
   cout << "1 = Encrypt the string. \n";
   cout << "2 = Decrypt the string. \n";
   cin >> x;

   switch(x)
   {
         case 1:
         for (i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] + 2;

         cout << "\n Encrypted String: " << str << endl;
         break;


      case 2:
         for (i = 0; (i < 100 && str[i] != '\0'); i++)
         str[i] = str[i] - 2;

      cout << "\n Decrypted string: " << str << endl;
      break;

      default:s
         cout << "\n Invalid Input !!!\n";
   }
   return 0;
}
