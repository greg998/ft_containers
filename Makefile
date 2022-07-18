# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiquiau <ggiquiau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:08:22 by ggiquiau          #+#    #+#              #
#    Updated: 2022/07/18 18:35:16 by ggiquiau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(addprefix tests/, \
								main.cpp \
								Tester.cpp \
								UnitTest.cpp \
)
					
OBJS            = ${SRCS:tests%.cpp=${OBJS_DIR}/$(DIR)%.o}

OBJS_DIR		= tests/objs


HEADERS			= $(addprefix includes/, vector.tpp iterator.tpp iterator_tags.hpp iterator_traits.tpp random_access_iterator.tpp algorithm.tpp type_traits.tpp utility.tpp map.tpp Rb_tree_iterator.tpp) $(addprefix tests/, Tester.hpp UnitTest.hpp)


CXX  			=  c++

CXXFLAGS		= -Wall -Wextra -std=c++98 -Iincludes -Itests -DNS=\"$(NS)\"
ifdef CMP
CXXFLAGS		+= -DCMP=1
endif

RM 				= rm -f

${OBJS_DIR}/$(DIR)/%.o:	tests/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)/$(DIR)
					${CXX} -c ${CXXFLAGS} -o $@ $<

all:
			make ft NS=ft DIR=ft
			make std NS=std DIR=std
			make cmp NS=ft DIR=cmp CMP=1

ft:		$(OBJS)
		${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o ft

std:	$(OBJS)
		${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o std
			
cmp:	$(OBJS)
		${CXX} ${OBJS} ${CXXFLAGS} ${LDFLAGS} -o cmp
		
clean:
				make clean2 DIR=ft
				make clean2 DIR=std
				make clean2 DIR=cmp
				@rm -fd ${OBJS_DIR} || true
				
clean2:
				${RM} ${OBJS}
				@rm -fd ${OBJS_DIR}/$(DIR) || true

fclean:			clean
				${RM} ft std cmp
				
re:
				${MAKE} fclean
				${MAKE} all

.PHONY:			all clean clean2 fclean re
