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
			return notify_fail("�����Ѿ��������ˣ�\n");
		
	      if( me->is_busy() )
		      return notify_fail("����һ��������û����ɣ�\n");
	     if( me->is_fighting() )
		      return notify_fail("�㻹��ר����ս�ɣ�\n");
        if ((int)me->query("jingli") < 500) 
           return notify_fail("��ľ�������������£�\n");  
      	message_vision(HIC"$N���ڵ��ϣ��Ĵ�Ѱ�ҡ�\n"NOR, me);
        me->start_busy(2);
        if(random(10)!=1) 
        {
           me->add("jingli",-200);
		   add("dig_times",-1);
           tell_room(environment(me), me->name() + "���˰��죬ֻŪ��һ���ࡣ\n", ({ me }));
           return notify_fail("�����˰��죬ʲôҲû�ҵ���\n");
        }
        else
        {
        obj = new(__DIR__"obj/danwan");
        message_vision(HIB"$N���ڷ���һ��ҩ�衣\n"NOR,me);
		set("dig_times",0);
        me->add("jingli", -500);
        obj->set("owner",me->query("id"));
        obj->move(me);       
        if(random(2)) obj=new("/d/sjsz/npc/huwei");
        else obj=new("/d/sjsz/npc/huwei");
        message_vision(HIB"ͻȻ����ǰ����һλ"+obj->name()+"��\n"NOR,me);
		    obj->set_temp("target", me->query("id") );
		    obj->setparty(6,me->query("max_pot")-100,me->query("combat_exp"));//�Ѷȣ��ȼ�������			
		    obj->move(environment(me));
		    obj->set_leader(me);			
		    obj->kill_ob(me);
		    message_vision(RED"$N������$nһ���ж���\n"NOR,obj,me);
        return 1;
       }
}