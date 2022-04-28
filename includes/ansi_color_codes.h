/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_color_codes.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 04:10:13 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/28 18:24:55 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSI_COLOR_CODES_H
# define ANSI_COLOR_CODES_H

/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 * 
 * Humbly adapted from:
 * 	https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
 */

//Regular text
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define PURPLE "\001\033[0;34m\002"
# define LILAC "\001\033[0;35m\002"
# define BLUE "\001\033[0;36m\002"
# define LGRAY "\001\033[0;37m\002"
# define GRAY "\001\033[0;90m\002"
# define LRED "\001\033[0;91m\002"
# define LGREEN "\001\033[0;92m\002"
# define CYAN "\001\033[0;93m\002"
# define ORANGE "\001\033[0;94m\002"
# define MAGENTA "\001\033[0;95m\002"
# define LYELLOW "\001\033[0;96m\002"
# define WHITE "\001\033[0;97m\002"

//Regular bold text
# define BGRAY "\001\033[1;30m\002"
# define BHGRAY "\001\033[1;90m\002"
# define BRED "\001\033[1;31m\002"
# define BHRED "\001\033[1;91m\002"
# define BGREEN "\001\033[1;32m\002"
# define BHGREEN "\001\033[1;92m\002"
# define BBLUE "\001\033[1;33m\002"
# define BHBLUE "\001\033[1;93m\002"
# define BYELLOW "\001\033[1;36m\002"
# define BHYELLOW "\001\033[1;96m\002"
# define BORANGE "\001\033[1;34m\002"
# define BHORANGE "\001\033[1;94m\002"
# define BMAGENTA "\001\033[1;35m\002"
# define BHMAGENTA "\001\033[1;95m\002"
# define BWHITE "\001\033[1;37m\002"
# define BHWHITE "\001\033[1;97m\002"

//Regular underline text
# define UBLACK "\001\033[4;30m\002"
# define URED "\001\033[4;31m\002"
# define UGREEN "\001\033[4;32m\002"
# define UYELLOW "\001\033[4;33m\002"
# define UPURPLE "\001\033[4;34m\002"
# define ULILAC "\001\033[4;35m\002"
# define UBLUE "\001\033[4;36m\002"
# define UWHITE "\001\033[4;37m\002"

//Regular background
# define BLACKB "\001\033[40m\002"
# define REDB "\001\033[41m\002"
# define YELLOWB "\001\033[43m\002"
# define LYELLOWB "\001\033[0;106m\002"
# define PURPLEB "\001\033[44m\002"
# define LILACB "\001\033[45m\002"
# define BLUEB "\001\033[46m\002"
# define CYANB "\001\033[0;103m\002"
# define GREENB "\001\033[42m\002"
# define ORANGEHB "\001\033[0;104m\002"
# define MAGENTAHB "\001\033[0;105m\002"
# define GRAYHB "\001\033[0;100m\002"
# define LGRAYB "\001\033[47m\002"
# define WHITEB "\001\033[0;107m\002"


//Reset
# define COLOUR_RESET "\001\033[0m\002"

#endif