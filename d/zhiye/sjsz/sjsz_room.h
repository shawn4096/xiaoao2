// sjsz_room.h 
//Modify By Renlai@xa
void reset()
{
	::reset();
	set("dig_times",3);
}
//
void init()
{
  add_action("do_search", "search");
}

int do_search(string arg)
{
        object obj, me;
        int j;
        me = this_player();
        if (query("dig_times")<1)
			return notify_fail("这里已经被翻遍了！\n");
		
	      if( me->is_busy() )
		      return notify_fail("你上一个动作还没有完成！\n");
	     if( me->is_fighting() )
		      return notify_fail("你还是专心作战吧！\n");
        if ((int)me->query("jingli") < 500) 
           return notify_fail("你的精力不够做这件事！\n");  
      	message_vision(HIC"$N蹲在地上，四处寻找。\n"NOR, me);
        me->start_busy(2);
        if(random(10)!=1) 
        {
           me->add("jingli",-200);
		   add("dig_times",-1);
           tell_room(environment(me), me->name() + "找了半天，只弄了一手泥。\n", ({ me }));
           return notify_fail("你找了半天，什么也没找到。\n");
        }
        else
        {
        obj = new(__DIR__"obj/danwan");
        message_vision(HIB"$N终于发现一颗药丸。\n"NOR,me);
		set("dig_times",0);
        me->add("jingli", -500);
        obj->set("owner",me->query("id"));
        obj->move(me);       
        if(random(2)) obj=new("/d/sjsz/npc/huwei");
        else obj=new("/d/sjsz/npc/huwei");
        message_vision(HIB"突然，面前跳出一位"+obj->name()+"。\n"NOR,me);
		    obj->set_temp("target", me->query("id") );
		    obj->setparty(6,me->query("max_pot")-100,me->query("combat_exp"));//难度，等级，经验			
		    obj->move(environment(me));
		    obj->set_leader(me);			
		    obj->kill_ob(me);
		    message_vision(RED"$N决定和$n一起行动。\n"NOR,obj,me);
        return 1;
       }
}