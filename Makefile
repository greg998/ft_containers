# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiquiau <ggiquiau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:08:22 by ggiquiau          #+#    #+#              #
#    Updated: 2022/06/06 13:34:49 by ggiquiau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(addprefix srcs/, \
								main.cpp \
)
					
OBJS            = ${SRCS:srcs%.cpp=${OBJS_DIR}%.o}

OBJS_DIR		= srcs/objs


HEADERS			= $(addprefix includes/, vector.tpp iterator.tpp iterator_tags.hpp iterator_traits.tpp random_access_iterator.tpp algorithm.tpp type_traits.tpp utility.tpp map.tpp)


CXX  			=  c++

ifdef TEST
CXXFLAGS		= -Wall -Wextra -g3 -std=c++98 -Iincludes 
else
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -Iincludes
endif


NAME 			= ex01

RM 				= rm -f


${OBJS_DIR}/%.o:	srcs/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					${CXX} -c ${CXXFLAGS} -o $@ $<

all:			${NAME}

${NAME}:		$(OBJS)
				${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o $@

				
test:
	@${MAKE} TEST=1
	@./${NAME}
debug:
	@${MAKE} TEST=1
	@valgrind --leak-check=full ./${NAME}
	
clean:
				${RM} ${OBJS} ${OBJS_BONUS}

fclean:
				${RM} ${OBJS} ${OBJS_BONUS} ${NAME}
				@rm -fd ${OBJS_DIR} || true

re:
				${MAKE} fclean
				${MAKE} all

.PHONY:			all clean fclean re
