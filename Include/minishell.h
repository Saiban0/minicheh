/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:19:25 by tom               #+#    #+#             */
/*   Updated: 2024/10/18 18:21:43 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libamoa.h"
# include "struct.h"
# include "parse.h"
# include "executing.h"
# include "error_management.h"
# include "builtins.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

#endif