/****    Software for Banking Industry    ****/
/****             "Pocket"                ****/
/*      Author:
        Radhey Shyam Meena
        B.Tech(IIT Bombay)
        Software Developer at CAE Simulation Technologies Pvt Ltd, Bangalore
        Permanent Address: Jaipur(Rajasthan)
        Mob. No. - +919986150142/+919680285628
*/
/*
    This software serves following objectives:
    1. Enable customers to create a new account
    2. Enable existing customers to withdraw money from their account
    3. Enable existing customers to update their profile (Password, Address, Mob No. etc.)
    4. Enable existing customers to deposit money in their accounts
    5. Enable existing customers to transfer money to the accounts of same bank
    6. Block a user for ‘one day’ when wrong password is entered 3 times
*/
#include<stdio.h>
#define ON 1
#define OFF 0

struct bank_user{
    int ac_num;
    char f_name[20];
    char l_name[20];
    char u_city[25];
    char u_state[25];
    char u_country[25];
    int u_bal;
    int passWd;
    int mob_no;
};
void user_interact(FILE *);
int userRecSize = sizeof(struct bank_user); // User Record Size
int flag;

int main(){
    int u_ch,exit_n = 1;
    int w_pwd_count=0,w_pwd[10],i=0,j,flag_w_pwd_3;
    w_pwd[0] = 0;
    char passWd2;
    struct bank_user u1,up1,u2,u21,u4;
    FILE *fp;
    fp = fopen("bank_users.dat","rb+");
    if(fp==NULL){
        u1.ac_num = 1000;
//        printf("First user Ac no. %d\n",u1.ac_num);
        fp = fopen("bank_users.dat","wb+");
        if(fp==NULL){
                printf("\n\t\t\t\t Error: File could not be created!!!\n");
        }
    }
while(exit_n!=0){
    fflush(stdin);
    printf("\n\t\t********** Hindustan Bank Welcomes You *************\n\n\n");
    printf("\t\t             Press 1: To Create new Account\n");
    printf("\t\t             Press 2: Existing Customer\n");
//    printf("\t\t             Press 3: To Display Customer list\n");
    printf("\t\t             Press 0: To exit\n");
    printf("\t\t             Enter your choice: ");
    scanf("%d",&u_ch);
    fflush(stdin);
    switch(u_ch){
        case 1:
                fflush(stdin);
                printf("\n\t\t              Enter First Name     : ");
                gets(u1.f_name);
                printf("\n\t\t              Enter Last Name      : ");
                gets(u1.l_name);
                printf("\n\t\t     Address: Enter Your City      : ");
                gets(u1.u_city);
                printf("\n\t\t              Enter Your State     : ");
                gets(u1.u_state);
                printf("\n\t\t              Enter Your Country   : ");
                gets(u1.u_country);
                printf("\n\t\t              Enter First Deposit  : ");
                scanf("%d",&u1.u_bal);
                printf("\n\t\t              Enter Your Mobile No.: ");
                scanf("%d",&u1.mob_no);
                printf("\n\t\t              Enter Password : ");
                fflush(stdin);
                scanf("%d",&u1.passWd);
                if(u1.ac_num==1000){
                       fwrite(&u1,userRecSize,1,fp);
                       u1.ac_num++;
                       printf("\n\t\tYour Account has been successfully created(Welcome first customer).\n");
                       printf("\n\t\tYour Account number is : %d.\n\n\n", u1.ac_num);
                       break;
                }
                else{
                       fseek(fp,-userRecSize,SEEK_END);
                       fread(&up1,userRecSize,1,fp);
                       u1.ac_num = up1.ac_num +1;
                       fseek(fp,0,SEEK_END);
                       fwrite(&u1,userRecSize,1,fp);
                       printf("\n\t\tYour Account Has been successfully created.\n");
                       printf("\n\t\tYour Account number is : %d.\n\n\n", u1.ac_num);
                       break;
                }
        case 2:
                printf("\n\t\t\tEnter your account Number: ");
                fflush(stdin);
                scanf("%d",&u2.ac_num);
                flag = OFF;
                fseek(fp,0,SEEK_SET);
                while(fread(&u21,userRecSize,1,fp)==1){
                      if(u2.ac_num==u21.ac_num){
                            flag = ON;
                            flag_w_pwd_3 = OFF;
                            fflush(stdin);

                            for(j=0;j<=i;j++){
                                  if(w_pwd[j] == u2.ac_num){
                                        printf("\n\t\t\tYou are blocked for the day. Try again tomorrow!!!\n\n");
                                        flag_w_pwd_3 = ON;
                                        break;
                                  }
                            }
                            if(flag_w_pwd_3==ON){
                                  break;
                            }
                            printf("\n\t\t\tPassword: ");                // Login Process
                            scanf("%d",&u2.passWd);
                            if(u2.passWd==u21.passWd){
                                  printf("\n\t\t\tWelcome %s %s\n\n",u21.f_name,u21.l_name);
                                  user_interact(fp);
                                  break;
                            }
                            else{
/*                                  for(j=0;j<=i;j++){
                                       if(w_pwd[j] == u2.ac_num){
                                             printf("\n\t\t\tYou are blocked for the day. Try again tomorrow!!!\n\n");
                                             flag_w_pwd_3 = ON;
                                             break;
                                       }
                                  } */

                                  printf("\n\t\t\tWrong Password\n");
                                  fseek(fp,-userRecSize,SEEK_CUR);
                                  w_pwd_count++;
                                  if(w_pwd_count>=3){
                                       w_pwd[i] = u2.ac_num;
                                       i++;
                                       printf("\n\t\t\t3 times wrong password, your account has been blocked for the day!!!\n\n");
                                       w_pwd_count = 0;
                                       break;
                                  }
//                                  pwd_w_3_ac_n =
//                                  break;
                            }
                            //break;
                      }
                }
                if(flag==OFF){
                      printf("\n\t\t\tNo person with this Ac no. exists!!!\n\n\n");
                }
                break;
/*        case 3:
                fseek(fp,0,SEEK_SET);
                if( fread(&u4,userRecSize,1,fp)==0){
                       printf("\n\t\t\tThere are no account holders to display!!!\n\t\t\tPlease create an account first!!!");
                }
                while(fread(&u4,userRecSize,1,fp)==1){
                       printf("\n\t\t\tName-%s, ac no-%d, Balance = %d\n",u4.f_name,u4.ac_num,u4.u_bal);
                }
                printf("\n\n");
                break;
*/
        case 0:
                exit_n = 0;
        default:
                printf("\n\t\t\tPlease Enter a valid choice!!!\n\n");

    }
}
    fclose(fp);
    return 0;
}

// Interaction with existing user
void user_interact(FILE *fp2){
    struct bank_user u2,u21,u23,u23u;
    int u_ch2=1,u_ch23,amt_withd,cur_pswd,n_c_pswd,n_pswd,cur_mob,amt_dipo;
    FILE *fp2u,*fp23b;            // using for funds transfer
    int flag23;                // using for funds transfer
    int amt_transf, ben_ac_n;        // using for funds transfer
    fseek(fp2,-userRecSize,SEEK_CUR);
    fread(&u2,userRecSize,1,fp2);
  while(u_ch2!=0){
    fflush(stdin);
    printf("\n\t\t\tPress 1: To Withdraw Money\n");
    printf("\n\t\t\tPress 2: To Deposit Money\n");
    printf("\n\t\t\tPress 3: To Transfer Money to another account of our Bank\n");
    printf("\n\t\t\tPress 4: To Change your Password\n");
    printf("\n\t\t\tPress 5: To Update your Profile\n");
    printf("\n\t\t\tPress 6: To View your complete profile\n");
    printf("\n\t\t\tPress 0: To Log-Out\n");
    printf("\n\t\t\tEnter your choice: ");
    scanf("%d",&u_ch2);
    fflush(stdin);
    switch(u_ch2){
        case 1:
                printf("\n\n\t\t\tEnter amount to withdraw: Rs.");
                scanf("%d",&amt_withd);
                if((u2.u_bal-500)<amt_withd){
                      printf("\n\t\t\tBalance t0o low to withdraw!!!\n");
                      printf("\n\t\t\tYour Hindustan Bank Account should always hold atleast Rs.500\n\n");
                      printf("\n\t\t\tContinue...");
                      getch();
                      printf("\n\n");
                      break;
                }
                else{
                      (u2.u_bal) = (u2.u_bal)-amt_withd;
                      fseek(fp2,-userRecSize,SEEK_CUR);
                      fwrite(&u2,userRecSize,1,fp2);                      // over-writing the whole user record to update the balance
                      printf("\n\t\t\tYour account balance is now: Rs.%d\n",u2.u_bal);
                      printf("\n\t\t\tCollect your Cash and wait for the receipt\n");
                      printf("\n\t\t\tContinue...");
                      getch();
                      printf("\n\n");
                      break;
                }
        case 2:
                printf("\n\n\t\t\tEnter amount to deposit: Rs.");
                scanf("%d",&amt_dipo);
                fseek(fp2,-userRecSize,SEEK_CUR);
                if(amt_dipo>0){
                      (u2.u_bal) = (u2.u_bal) + amt_dipo;                // Depositing money in the account
                      fwrite(&u2,userRecSize,1,fp2);
                      printf("\n\t\t\tYour account balance is now: Rs.%d\n",u2.u_bal);
                      printf("\n\t\t\tAmount Successfully Deposited in Your Hindustan Bank Account\n\n");
                      printf("\n\t\t\tContinue...");
                      getch();
                      printf("\n\n");
                      break;
                }
                else{
                      printf("\n\t\t\tInvalid Amount!!!\n\n");
                      printf("\n\t\t\tContinue...");
                      getch();
                      printf("\n\n");
                      break;
                }
                break;
        case 3:
/*                printf("\n\n\t\t\tUnder maintenance. Please try again later!!!\n\n");
              break;    */
               flag23 = OFF;
               printf("\n\n\t\t\tEnter Beneficiary's account number: ");
               scanf("%d",&ben_ac_n);
               fseek(fp2,0,SEEK_SET);
               while(fread(&u23,userRecSize,1,fp2)==1){
                     if(u23.ac_num==ben_ac_n){
                           flag23 = ON;
                           //printf("\n\n\t\t\tEnter your profile password: ");
                           printf("\n\t\t\tEnter the amount(in Rupees) to be transfered: ");
                           scanf("%d",&amt_transf);
                           if((u2.u_bal-500)<amt_transf){
                                 printf("\n\t\t\tBalance too low to Transfer Funds!!!\n");
                                 printf("\n\t\t\tYour account balance is: Rs.%d\n",u2.u_bal);
                                 printf("\n\t\t\tYour Hindustan Bank Account should always hold atleast Rs.500\n\n");
                                 printf("\n\t\t\tContinue...");
                                 getch();
                                 printf("\n\n");
                                 break;           // to break the while loop
                           }
                           else{
                                 u23.u_bal = u23.u_bal + amt_transf;            // Beneficiery's account balance increased by amt_transf
                                 fseek(fp2,-userRecSize,SEEK_CUR);
                                 fwrite(&u23,userRecSize,1,fp2);
//                                 printf("\nafter updating ben's  info struct fp2u = %u, fp2=%u, fp23b=%u",fp2u,fp2,fp23b);
                                 fseek(fp2,0,SEEK_SET);
                                 while(fread(&u23u,userRecSize,1,fp2)==1){           // looking somewhat awkward.. must be another good method :)
                                       if(u2.ac_num==u23u.ac_num){
                                             u2.u_bal = u2.u_bal - amt_transf;
                                             fseek(fp2,-userRecSize,SEEK_CUR);
                                             fwrite(&u2,userRecSize,1,fp2);  //Quite NOT Right
                                             break;
                                       }
  //                               printf("\nafter updating user's  info struct fp2u = %u, fp2=%u, fp23b=%u",fp2u,fp2,fp23b);
                                 }
                                 printf("\n\t\t\tAmount Successfully Transferred\n\n");
                                 printf("\n\t\t\tContinue...");
                                 getch();
                                 printf("\n\n");
                                 break;           // to break the while loop
                           }
                     }
               }
               if(flag23 == OFF){
                     printf("\n\t\t\tNo user exits with this account number\n\n");
                     printf("\n\t\t\tContinue...");
                     getch();
                     printf("\n\n");
                     break;
               }
               break; // breaking the switch case
        case 4:
                printf("\n\n\t\t\tEnter your current password: ");
                fflush(stdin);
                scanf("%d",&cur_pswd);
                if(cur_pswd==(u2.passWd)){
                     printf("\n\t\t\tEnter new Password: ");
                     scanf("%d",&n_pswd);
                     fflush(stdin);
                     printf("\n\t\t\tConfirm Password: ");
                     scanf("%d",&n_c_pswd);
                     if(n_pswd == n_c_pswd){
                          (u2.passWd) = n_pswd;
                          fseek(fp2,-userRecSize,SEEK_CUR);
                          fwrite(&u2,userRecSize,1,fp2);                          // over-writing the whole user record to update the password
                          printf("\n\t\t\tPassword has been changed successfully!!\n\n");
                          printf("\n\t\t\tContinue...");
                          getch();
                          printf("\n\n");
                          break;
                     }
                     else{
                          printf("\n\t\t\tPassword do not match!!!\n\n");
                          printf("\n\t\t\tContinue...");
                          getch();
                          printf("\n\n");
                          break;
                     }
                }
                else{
                     printf("\n\t\t\tWrong Password!!!\n\n");
                     printf("\n\t\t\tContinue...");
                     getch();
                     printf("\n\n");
                     break;
                }
        case 5:
                printf("\n");
                printf("\n\t\t\tPress 1: To change your Address\n");
                printf("\n\t\t\tPress 2: To change your Mobile Number\n");
                printf("\n\t\t\tEnter your choice: ");
                fflush(stdin);
                scanf("%d",&u_ch23);
                switch(u_ch23){
                     case 1:
                          printf("\n\t\t\tEnter New City: ");
                          fflush(stdin);
                          scanf("%s",u2.u_city);
                          printf("\n\t\t\tEnter State: ");
                          scanf("%s",u2.u_state);
                          printf("\n\t\t\tEnter Country: ");
                          scanf("%s",u2.u_country);
                          fseek(fp2,-userRecSize,SEEK_CUR);
                          fwrite(&u2,userRecSize,1,fp2);                          // over-writing the whole user record to change the address
                          printf("\n\t\t\tYour Address has been updated\n\n");
                          printf("\n\t\t\tContinue...");
                          getch();
                          printf("\n\n");
                          break;
                     case 2:
                          printf("\n\t\t\tEnter current mobile number: ");
                          scanf("%d",&cur_mob);
                          if(cur_mob==u2.mob_no){
                               printf("\n\t\t\tEnter new Mobile number: ");
                               scanf("%d",&u2.mob_no);
                               fseek(fp2,-userRecSize,SEEK_CUR);
                               fwrite(&u2,userRecSize,1,fp2);        // over-writing the whole user record to change the mobile number
                               printf("\n\t\t\tYour Mobile Number has been updated\n\n");
                               printf("\n\t\t\tContinue...");
                               getch();
                               printf("\n\n");
                               break;
                          }
                          else{
                               printf("\n\t\t\tYou have entered Wrong Mobile Number! Better luck next time\n\n");
                               printf("\n\t\t\tContinue...");
                               getch();
                               printf("\n\n");
                               break;
                          }
                          break;
                     default:
                          printf("\n\t\t\tThat was an incorrect choice!!!\n\n");
                          printf("\n\t\t\tContinue...");
                          getch();
                          printf("\n\n");
                          break;
                }   // inner switch() in outer 'case 3:' ends here
                break;
        case 6:
                printf("\n\t\t        Account Holder's Information\n");
                printf("\n\t\t\tName                 : %s %s",u2.f_name,u2.l_name);
                printf("\n\t\t\tAddress              : %s, %s, %s",u2.u_city,u2.u_state,u2.u_country);
                printf("\n\t\t\tPhone Number         : %d",u2.mob_no);
                printf("\n\t\t\tBalance(in Rupees)   : %d\n",u2.u_bal);
                printf("\n\t\t\tContinue...");
                getch();
                printf("\n\n");
                break;
        case 0:
                printf("\n\t\t\tThank you for visiting Hindustan Bank\n\n");
                printf("\n\t\t\tSuccessfully Logged out\n\n\n");
                break;
        default:
                printf("\n\t\t\tPlease enter a valid choice!!!\n\n");
                break;
    }
  }    // outer-while loop ends here
}
