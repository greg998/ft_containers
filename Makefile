# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiquiau <ggiquiau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:08:22 by ggiquiau          #+#    #+#              #
#    Updated: 2022/05/11 16:14:00 by ggiquiau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(addprefix srcs/, \
								main.cpp \
)
					
OBJS            = ${SRCS:srcs%.cpp=${OBJS_DIR}%.o}

OBJS_DIR		= srcs/objs


HEADERS			= $(addprefix includes/, vector.tpp)

CXX  			=  c++

CXXFLAGS		= -Wall -Wextra -std=c++98 -Iincludes -g3


NAME 			= ex01

RM 				= rm -f


${OBJS_DIR}/%.o:	srcs/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					${CXX} -c ${CXXFLAGS} -o $@ $<

all:			${NAME}

${NAME}:		$(OBJS)
				${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o $@

				

clean:
				${RM} ${OBJS} ${OBJS_BONUS}

fclean:
				${RM} ${OBJS} ${OBJS_BONUS} ${NAME}
				@rm -fd ${OBJS_DIR} || true

re:
				${MAKE} fclean
				${MAKE} all

.PHONY:			all clean fclean re
