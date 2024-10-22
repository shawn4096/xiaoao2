// room.c
// let npc with setting "no_return" not to come back to their
// original place, when it refreshes.
// 1998-02-13, @jyqxz
 
#pragma save_binary

#include <dbase.h>
#include <room.h>


inherit F_DBASE;
inherit F_CLEAN_UP;

nosave mapping doors;

void fuben_reset();
int query_max_encumbrance() { return 100000000000; }



void init()
{
	object me = this_player();	
    object* team;
	
	team=me->query_team();	
	   if (team) 
	  {		
		if (team[0] == me) {	
	          
	          add_action("do_up","up");
		}
		      add_action("do_leave","leavefb");
	          add_action("do_quit","quit");
	  }
	  else
	  {
		      add_action("do_leave","leavefb");
	          add_action("do_quit","quit");
	          add_action("do_up","up");
	  }
	  
	  if (wizardp(me))	{
		     add_action("do_dismiss","dismiss");
	  }
	
    	
	remove_call_out("fuben_reset");
	call_out("fuben_reset", 100);
	
}


int do_dismiss()
{
	        set("over",1);
	        fuben_reset();
			return 1;
}

int do_up()
{
	object me=this_player();
	
	if(present("menggu wushi", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}	
	return 1;	
}



int do_quit()
{
	
	write("这里不能退出游戏。\n");	
	return 1;	
}

int do_leave()
{
	object me=this_player();
	object* team;
	
	team=me->query_team();	
	
	//队长不在，队员可以离开
	if (query("leader"))
	{
		if(!present(query("leader"), environment(me)))
		{
			set("over",1);
	        fuben_reset();
			return 1;
		}
	}
	
	if(present("mingjiao jiaozhong", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
	
	
	if(present("xixia wushi", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
	
	if(present("menggu wushi", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
     
     if(present("attacker", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
	
	
	if (team) 
	{
		
		if (team[0] != me) {
		  write("只有队长才能发指令离开。\n");	
		return 1;
	    }
		remove_call_out("fuben_reset");
	//call_out("fuben_reset", 0);
	    set("over",1);
	    fuben_reset();
		return 1;		
		
	}		
	else
	{
	remove_call_out("fuben_reset");
	//call_out("fuben_reset", 0);
	    set("over",1);
	    fuben_reset();
		return 1;		
	}
}

void fuben_reset()
{
	
}




object make_inventory(string file)
{
        object ob;

        ob = new(resolve_path(0, file));
        ob->move(this_object());
        ob->set("startroom", base_name(this_object()));
        return ob;
}

// it's changed to let some npcs don't come back when refresh.
void reset()
{
        mapping ob_list, ob;
        string *list;
        int i,j;

        //
        // Check loaded objects to match the objects specified in "objects"
        // while query("objects") is 
        // ([ <object filename>: <amount>, ..... ])
        // and query_temp("objects") is
        // ([ <object filename>: ({ob1, ob2, ...}), .... ])
        //
        set("no_clean_up", 0);
        ob_list = query("objects");
        if( !mapp(ob_list) ) return;
        
        if( !mapp(ob = query_temp("objects")) )
                ob = allocate_mapping(sizeof(ob_list));
        list = keys(ob_list);
        for(i=0; i<sizeof(list); i++) {
                // Allocate an array if we have multiple same object specified.
                if(     undefinedp(ob[list[i]])
                &&      intp(ob_list[list[i]])
                &&      ob_list[list[i]] > 1 )
                        ob[list[i]] = allocate(ob_list[list[i]]);

                switch(ob_list[list[i]]) {
                case 1:
                        if( !ob[list[i]] ) ob[list[i]] = make_inventory(list[i]);
// don't let npc with setting "no_return" come back
			if ( ob[list[i]]->query("no_return") ) break;

                        if ( environment(ob[list[i]]) != this_object()
//                      &&      ob[list[i]]->is_character()
                        &&      !ob[list[i]]->return_home(this_object()) ) {
                                        ob[list[i]] = make_inventory(list[i]);
                                        add("no_clean_up", 1);
                        }
                        break;
                default:
                        for(j=0; j<ob_list[list[i]]; j++) {
                                // If the object is gone, make another one.
                                if( !objectp(ob[list[i]][j]) ) {
                                        ob[list[i]][j] = make_inventory(list[i]);
                                        continue;
                                }
                                // Try to call the wandering npc come back here.
//  don't let npc with setting "no_return" come back
				if ( ob[list[i]]->query("no_return") ) {
					set_temp("objects",ob);
					return;
				}

                                if( environment(ob[list[i]][j]) != this_object()
//                              &&      ob[list[i]][j]->is_character()
                                &&      !ob[list[i]][j]->return_home(this_object())) {
                                                ob[list[i]][j] = make_inventory(list[i]);
                                                add("no_clean_up", 1);
                                }
                        }
                }
        }
        set_temp("objects", ob);
}

// Redirect item_desc of the door to this function in default.
string look_door(string dir)
{
        if( !mapp(doors) || undefinedp(doors[dir]) )
                return "你要看什么？\n";
        if( doors[dir]["status"] & DOOR_CLOSED )
                return "这个" + doors[dir]["name"] + "是关着的。\n";
        else
                return "这个" + doors[dir]["name"] + "是开着的。\n";
}

varargs int open_door(string dir, int from_other_side)
{
        mapping exits;
        object ob;

        if( !mapp(doors) || undefinedp(doors[dir]) )
                return notify_fail("这个方向没有门。\n");

        if( !(doors[dir]["status"] & DOOR_CLOSED) )
                return notify_fail( doors[dir]["name"] + "已经是开着的了。\n");

        exits = query("exits");
        if( !mapp(exits) || undefinedp(exits[dir]) )
                error("Room: open_door: attempt to open a door with out an exit.\n");

        if( from_other_side )
                message("vision", "有人从另一边将" + doors[dir]["name"] + "打开了。\n", this_object());
        else if( objectp(ob = find_object(exits[dir])) ) {
                if( !ob->open_door(doors[dir]["other_side_dir"], 1) ) return 0;
        }

        doors[dir]["status"] &= (!DOOR_CLOSED);
        return 1;
}

varargs int close_door(string dir, int from_other_side)
{
        mapping exits;
        object ob;

        if( !mapp(doors) || undefinedp(doors[dir]) )
                return notify_fail("这个方向没有门。\n");

        if( (doors[dir]["status"] & DOOR_CLOSED) )
                return notify_fail( doors[dir]["name"] + "已经是关着的了。\n");

        exits = query("exits");
        if( !mapp(exits) || undefinedp(exits[dir]) )
                error("Room: close_door: attempt to open a door with out an exit.\n");

        if( from_other_side )
                message("vision", "有人从另一边将" + doors[dir]["name"] + "关上了。\n", this_object());
        else if( objectp(ob = find_object(exits[dir])) ) {
                if( !ob->close_door(doors[dir]["other_side_dir"], 1) ) return 0;
        }

        doors[dir]["status"] |= DOOR_CLOSED;
        return 1;
}

int check_door(string dir, mapping door)
{
        // If we have no responding door, assume it is correct.
        if( !mapp(doors) || undefinedp(doors[dir]) ) return 1;

        door["status"] = doors[dir]["status"];
        return 1;
}

varargs void create_door(string dir, mixed data, string other_side_dir, int status)
{
        mapping d, exits, item_desc;
        object ob;

        exits = query("exits");
        if( !mapp(exits) || undefinedp(exits[dir]) )
                error("Room: create_door: attempt to create a door without exit.\n");

        // Compact mode.
        if( stringp(data) ) {
                d = allocate_mapping(4);
                d["name"] = data;
                d["id"] = ({ dir, data, "door" });
                d["other_side_dir"] = other_side_dir;
                d["status"] = status;
        } else if( mapp(data) )
                d = data;
        else
                error("Create_door: Invalid door data, string or mapping expected.\n");

        set("item_desc/" + dir, (: look_door, dir :) );

        if( objectp(ob = find_object(exits[dir])) ) {
                if( !ob->check_door(other_side_dir, d) )
                        return;
        }

        if( !mapp(doors) ) doors = ([ dir: d ]);
        else doors[dir] = d;
}

mapping query_doors() { return doors; }

mixed query_door(string dir, string prop)
{
        if( !mapp(doors) || undefinedp(doors[dir]) ) return 0;
        else return doors[dir][prop];
}

int valid_leave(object me, string dir)
{
        if( mapp(doors) && !undefinedp(doors[dir]) ) {
                if( doors[dir]["status"] & DOOR_CLOSED )
                        return notify_fail("你必须先把" + doors[dir]["name"] + "打开！\n");
                // if ( door[dir]["status"] & DOOR_HAS_TRAP ) ....
        }
        return 1;
}

void setup()
{
        seteuid(getuid());
        this_object()->reset();
}
