cmake_minimum_required(VERSION 3.17)
project(cli_rpg)
enable_testing()
set(CMAKE_CXX_STANDARD 14)
if(MSVC)
	#Microsoft "Helpfully" defines it's own min/max functions
	add_compile_definitions(NOMINMAX)

	#if you are compiling with VisualStudio make sure to uncomment the line below.
	#If you're using CLion or similar that puts the builds in the project directory then the release type. Don't
	#add_compile_definitions(VISUAL_STUDIO_BUILD)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /W3")
	set(CMAKE_CXX_FLAGS_Debug "${CMAKE_CXX_FLAGS} /Od")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g3 ")
	#since CLion decides that you debug from the damn release buildl always instead of from debug and won't let you change that.
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()



#the libraries

#basic includes stuff
add_library(includes_lib OBJECT
		includes.hxx)
#because of windows
set_target_properties(includes_lib PROPERTIES LINKER_LANGUAGE CXX)

#items related stuff
add_library(items_lib OBJECT
		classes/items/potion.hxx classes/items/item.hxx classes/items/weapon.hxx classes/items/armor.hxx)
set_target_properties(includes_lib PROPERTIES LINKER_LANGUAGE CXX)

#inventory related stuff
add_library(inventory_lib OBJECT
		classes/containers/inventory.hxx
		classes/containers/loot_table.hxx)
set_target_properties(inventory_lib PROPERTIES LINKER_LANGUAGE CXX)

#actors related stuff
add_library(actors_lib OBJECT
		classes/fighters/actor.hxx
		classes/fighters/mob.hxx
		classes/fighters/player.hxx
		)
set_target_properties(actors_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(menu_lib OBJECT
		menus/menu.hxx
		menus/map_movement.hxx
		menus/inventory_menu.hxx
		menus/shop.hxx
		menus/battle.hxx
		menus/tutorial_menu.hxx)
set_target_properties(menu_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(data_lib OBJECT
		data/items.hxx
		data/mobs.hxx
		data/menus.hxx
		data/shops.hxx)
set_target_properties(data_lib PROPERTIES LINKER_LANGUAGE CXX)


#Executables start below

#all tests first

#fighters/actors stuff
add_executable(test_fighters
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		tests/actor_test.cpp
		)

#battle demo
add_executable(battle_demo
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/battle/battle_system.hxx
		menus/battle.hxx
		demos/battle_demo.cpp
		)


#test the battle
add_executable(test_battle
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/battle/battle_system.hxx
		menus/battle.hxx
		tests/battle_test.cpp
		)

#test the map, will have to make this a library eventually.
add_executable(test_map
		includes.hxx
		classes/maps/room.hxx
		classes/maps/map.hxx
		tests/map_test.cpp
		)

#build the item test binary.
add_executable(test_items
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		tests/item_test.cpp
		tests/item_test.cpp)

add_executable(test_inventory
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		classes/containers/shop_inventory.hxx
		tests/inventory_test.cpp
		)

add_executable(test_shop
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/containers/shop_inventory.hxx
		classes/shop_keeper.hxx
		tests/shop_test.cpp
		)


#demo/build files below here
add_executable(inventory_demo
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		classes/containers/shop_inventory.hxx
		menus/menu.hxx
		menus/inventory_menu.hxx
		demos/inventory_demo.cpp
		)


add_executable(shop_demo
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/containers/shop_inventory.hxx
		classes/shop_keeper.hxx
		menus/menu.hxx
		menus/shop.hxx
		demos/shop_demo.cpp
		)


add_executable(tutorial_demo
		#all the libraries
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/shop_keeper.hxx
		#all the menus
		$<TARGET_OBJECTS:menu_lib>
		#data
		$<TARGET_OBJECTS:data_lib>
		#main binary
		demos/tutorial_demo.cpp
		)
add_executable(save_demo
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		$<TARGET_OBJECTS:data_lib>
		demos/load_save_demo.cpp
		)

add_executable(test_save
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		$<TARGET_OBJECTS:data_lib>
		tests/load_save_test.cpp
		)


add_executable(dangling_pointers
		#all the libraries
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		$<TARGET_OBJECTS:menu_lib>
		classes/shop_keeper.hxx
		#data
		$<TARGET_OBJECTS:data_lib>
		#main binary
		main.cpp
		main.hxx)




#have to make sure this works on windows first.
if(MSVC)
	#Test the battle system
#	add_test(NAME "Battle_Module"
#			COMMAND test_battle.exe)
	#Test the Actor class and children classes.
	add_test(NAME "Actor_Module"
			COMMAND test_fighters.exe)

	#Test the Inventory Module and related children classes.
	add_test(NAME "Inventory_Module"
			COMMAND test_inventory.exe)

	#Item Module
	add_test(NAME "Item_Module"
			COMMAND test_items.exe)

	#shop Module
	add_test(NAME "Shop_Module"
			COMMAND test_shop.exe)

	#save system
	add_test(NAME "Save_System"
			COMMAND test_save)

else()
	#Test the battle system
#	add_test(NAME "Battle_Module"
#			COMMAND ./test_battle)
	#Test the Actor class and children classes.
	add_test(NAME "Actor_Module"
			COMMAND ./test_fighters)
	#Test the Inventory Module and related children classes.
	add_test(NAME "Inventory_Module"
			COMMAND ./test_inventory)

	add_test(NAME "Item_Module"
			COMMAND ./test_items)

	add_test(NAME "Shop_Module"
			COMMAND ./test_shop)

	add_test(NAME "Save_System"
			COMMAND ./test_save)

endif()
