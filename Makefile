# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiquiau <ggiquiau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:08:22 by ggiquiau          #+#    #+#              #
#    Updated: 2022/07/15 15:54:43 by ggiquiau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(addprefix tests/, \
								main.cpp \
								Tester.cpp \
								UnitTest.cpp \
)
					
OBJS            = ${SRCS:tests%.cpp=${OBJS_DIR}/$(NS)%.o}

OBJS_DIR		= tests/objs


HEADERS			= $(addprefix includes/, vector.tpp iterator.tpp iterator_tags.hpp iterator_traits.tpp random_access_iterator.tpp algorithm.tpp type_traits.tpp utility.tpp map.tpp Rb_tree_iterator.tpp) $(addprefix tests/, Tester.hpp UnitTest.hpp)


CXX  			=  c++

CXXFLAGS		= -Wall -Wextra -std=c++98 -Iincludes -Itests -DNS=\"$(NS)\"

RM 				= rm -f

${OBJS_DIR}/$(NS)/%.o:	tests/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)/$(NS)
					${CXX} -c ${CXXFLAGS} -o $@ $<

all:
			make ft NS=ft
			make std NS=std

ft:		$(OBJS)
		${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o ft

std:	$(OBJS)
		${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o std
			
	
clean:
				make clean2 NS=ft
				make clean2 NS=std
				@rm -fd ${OBJS_DIR} || true
				
clean2:
				${RM} ${OBJS}
				@rm -fd ${OBJS_DIR}/$(NS) || true

fclean:			clean
				${RM} ft std
				
re:
				${MAKE} fclean
				${MAKE} all

.PHONY:			all clean clean2 fclean re
