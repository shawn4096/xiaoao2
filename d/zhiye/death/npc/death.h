//Death.h By Jpei 2011
//����������

void init()
{
	object me = this_player();

        ::init();
     me->delete_temp("no_fight");
	if (!userp(me)) return;
	//|| me->query("combat_exp") < 10000 && me->query("death_count") > (me->query("death_times") * 10)

    //����ǻ��ˣ�ֱ���߳�ȥ
     if(!me->is_ghost() && !wizardp(me))
	 {
		 command("say �ֻ��޳�������֮�ˣ�Ӧ���ص�����ȥ���ǡ�");
		 message_vision("������ʿ���˳���������$N��һ�ξͲ����ˣ�\n", me);
         me->reincarnate();
		 me->move(REVIVE_ROOM);
         tell_object(me, HIW"��һ��������������ȴ�����Լ��Ѿ��ص������䣡\n"NOR);
         message("vision","���Ȼ������Ӱ��֪��ʲô�ط�ð�˳�����\n", environment(me), me);
		 return;
	 }
	 
	      //remove_call_out("death_stage");
	  if (me->query_temp("special_poison",1))
                call_out("death_stage", 20, me, 0);
        else
                call_out("death_stage", 40, me, 0);

}

void death_stage(object ob, int stage)
{
        if( !ob || !present(ob) ) return;

        if( !ob->is_ghost() ) {
                command("say �ֻ��޳�������֮�ˣ�Ӧ���ص�����ȥ���ǡ�");
                message_vision("������ʿ���˳���������$N��һ�ξͲ����ˣ�\n", ob);
                ob->reincarnate();
                if (ob->query("enter_wuguan")) ob->move(START_ROOM);
                else ob->move(REVIVE_ROOM);
                tell_object(ob, HIW"��һ��������������ȴ�����Լ��Ѿ��ص������䣡\n"NOR);
                message("vision","���Ȼ������Ӱ��֪��ʲô�ط�ð�˳�����\n", environment(ob), ob);
                return;
        }

	message_vision(death_msg[stage],this_object(),ob);
        if( ++stage < sizeof(death_msg) ) {
                call_out( "death_stage", 5, ob, stage );
                return;
        } else
              ob->reincarnate();
        UPDATE_D->get_cloth(ob);
              ob->delete_temp("special_die");
              ob->setup();
              ob->set("body", USER_OB);//�������� by renlai			  
              ob->set_temp("death_relife",1);
              ob->move(REVIVE_ROOM);

//��һ������ı�ǣ�����Ѫ�������·���Ȼ����˶���ȥ�����¡��ڸ����������������ˡ�
        
message("vision","���Ȼ�������Զ���һ����Ӱ����������Ӱ�ֺ����Ѿ�������ܾ��ˣ�ֻ����һֱû������\n", REVIVE_ROOM, ob );
}
