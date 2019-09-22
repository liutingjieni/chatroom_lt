/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2019年08月07日 星期三 09时02分25秒
 ************************************************************************/

#include <stdio.h>
#include "client_menu.h"
#include "client_init.h"
#include "client_io.h"
#include <stdlib.h>



int main()
{
    char choice;
    int cli_fd = init();
    main_login(cli_fd);
}




