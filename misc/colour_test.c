/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:07:54 by coder             #+#    #+#             */
/*   Updated: 2022/04/28 17:35:31 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	
	printf(BRED "Hey this is the color red, and it's bold!" COLOUR_RESET);
	printf("\n");
	printf(RED "If " BLU "you " YEL "are " GRN "bo" COLOUR_RESET "red " CYN "do " MAG "this!" COLOUR_RESET); 
	printf("\n");
	printf(BRED "If " BBLU "you " BYEL "are " BGRN "bo" COLOUR_RESET "red " BCYN "do " BMAG "this!" COLOUR_RESET); 
	printf("\n");
	printf(URED "If " UBLU "you " UYEL "are " UGRN "bo" COLOUR_RESET "red " UCYN "do " UMAG "this!" COLOUR_RESET);
	printf("\n");

    printf(BLK "this is colour BLK. code: 0;30m" COLOUR_RESET);
	printf("\n");
    printf(RED "this is colour RED. code: 0;31m" COLOUR_RESET);
	printf("\n");
    printf(GRN "this is colour GRN. code: 0;32m" COLOUR_RESET);
	printf("\n");
    printf(YEL "this is colour YEL. code: 0;33m" COLOUR_RESET);
	printf("\n");
    printf(BLU "this is colour BLU. code: 0;34m" COLOUR_RESET);
	printf("\n");
    printf(MAG "this is colour MAG. code: 0;35m" COLOUR_RESET);
	printf("\n");
    printf(CYN "this is colour CYN. code: 0;36m" COLOUR_RESET);
	printf("\n");
    printf(WHT "this is colour WHT. code: 0;37m" COLOUR_RESET);
	printf("\n");
    printf(BBLK "this is colour BBLK. code: 1;30m" COLOUR_RESET);
	printf("\n");
    printf(BRED "this is colour BRED. code: 1;31m" COLOUR_RESET);
	printf("\n");
    printf(BGRN "this is colour BGRN. code: 1;32m" COLOUR_RESET);
	printf("\n");
    printf(BYEL "this is colour BYEL. code: 1;33m" COLOUR_RESET);
	printf("\n");
    printf(BBLU "this is colour BBLU. code: 1;34m" COLOUR_RESET);
	printf("\n");
    printf(BMAG "this is colour BMAG. code: 1;35m" COLOUR_RESET);
	printf("\n");
    printf(BCYN "this is colour BCYN. code: 1;36m" COLOUR_RESET);
	printf("\n");
    printf(BWHT "this is colour BWHT. code: 1;37m" COLOUR_RESET);
	printf("\n");
    printf(UBLK "this is colour UBLK. code: 4;30m" COLOUR_RESET);
	printf("\n");
    printf(URED "this is colour URED. code: 4;31m" COLOUR_RESET);
	printf("\n");
    printf(UGRN "this is colour UGRN. code: 4;32m" COLOUR_RESET);
	printf("\n");
    printf(UYEL "this is colour UYEL. code: 4;33m" COLOUR_RESET);
	printf("\n");
    printf(UBLU "this is colour UBLU. code: 4;34m" COLOUR_RESET);
	printf("\n");
    printf(UMAG "this is colour UMAG. code: 4;35m" COLOUR_RESET);
	printf("\n");
    printf(UCYN "this is colour UCYN. code: 4;36m" COLOUR_RESET);
	printf("\n");
    printf(UWHT "this is colour UWHT. code: 4;37m" COLOUR_RESET);
	printf("\n");
    printf(BLKB "this is colour BLKB. code: e[40m" COLOUR_RESET);
	printf("\n");
    printf(REDB "this is colour REDB. code: e[41m" COLOUR_RESET);
	printf("\n");
    printf(GRNB "this is colour GRNB. code: e[42m" COLOUR_RESET);
	printf("\n");
    printf(YELB "this is colour YELB. code: e[43m" COLOUR_RESET);
	printf("\n");
    printf(BLUB "this is colour BLUB. code: e[44m" COLOUR_RESET);
	printf("\n");
    printf(MAGB "this is colour MAGB. code: e[45m" COLOUR_RESET);
	printf("\n");
    printf(CYNB "this is colour CYNB. code: e[46m" COLOUR_RESET);
	printf("\n");
    printf(WHTB "this is colour WHTB. code: e[47m" COLOUR_RESET);
	printf("\n");
    printf(BLKHB "this is colour BLKHB. code: 0;100m" COLOUR_RESET);
	printf("\n");
    printf(REDHB "this is colour REDHB. code: 0;101m" COLOUR_RESET);
	printf("\n");
    printf(GRNHB "this is colour GRNHB. code: 0;102m" COLOUR_RESET);
	printf("\n");
    printf(YELHB "this is colour YELHB. code: 0;103m" COLOUR_RESET);
	printf("\n");
    printf(BLUHB "this is colour BLUHB. code: 0;104m" COLOUR_RESET);
	printf("\n");
    printf(MAGHB "this is colour MAGHB. code: 0;105m" COLOUR_RESET);
	printf("\n");
    printf(CYNHB "this is colour CYNHB. code: 0;106m" COLOUR_RESET);
	printf("\n");
    printf(WHTHB "this is colour WHTHB. code: 0;107m" COLOUR_RESET);
	printf("\n");
    printf(HBLK "this is colour HBLK. code: 0;90m" COLOUR_RESET);
	printf("\n");
    printf(HRED "this is colour HRED. code: 0;91m" COLOUR_RESET);
	printf("\n");
    printf(HGRN "this is colour HGRN. code: 0;92m" COLOUR_RESET);
	printf("\n");
    printf(HYEL "this is colour HYEL. code: 0;93m" COLOUR_RESET);
	printf("\n");
    printf(HBLU "this is colour HBLU. code: 0;94m" COLOUR_RESET);
	printf("\n");
    printf(HMAG "this is colour HMAG. code: 0;95m" COLOUR_RESET);
	printf("\n");
    printf(HCYN "this is colour HCYN. code: 0;96m" COLOUR_RESET);
	printf("\n");
    printf(HWHT "this is colour HWHT. code: 0;97m" COLOUR_RESET);
	printf("\n");
    printf(BHBLK "this is colour BHBLK. code: 1;90m" COLOUR_RESET);
	printf("\n");
    printf(BHRED "this is colour BHRED. code: 1;91m" COLOUR_RESET);
	printf("\n");
    printf(BHGRN "this is colour BHGRN. code: 1;92m" COLOUR_RESET);
	printf("\n");
    printf(BHYEL "this is colour BHYEL. code: 1;93m" COLOUR_RESET);
	printf("\n");
    printf(BHBLU "this is colour BHBLU. code: 1;94m" COLOUR_RESET);
	printf("\n");
    printf(BHMAG "this is colour BHMAG. code: 1;95m" COLOUR_RESET);
	printf("\n");
    printf(BHCYN "this is colour BHCYN. code: 1;96m" COLOUR_RESET);
	printf("\n");
    printf(BHWHT "this is colour BHWHT. code: 1;97m" COLOUR_RESET);
	printf("\n");
}