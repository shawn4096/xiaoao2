
#include <ansi.h>

//Ѫ��

string ask_xuedao()
{
        object me=this_player() , weapon;
        int i;

        if ((string)me->query("family/family_name") != "Ѫ����"&&me->query("family/master_id")!="xudao laozu")
			return "Ѫ������Ѫ����������������Ե�޹ʣ�ƾʲô���㣿\n";
	
        if(!me->query("quest/xd/dichuan")) return "���Ѫ���ŵմ����ӣ�\n";
		
		if (me->query("job_time/ѩ�ȼ�ս")<200) return "���ѩ�ȼ�ս������200�Σ�\n";
		
        weapon = present("xue dao", this_object());
                if(!objectp(weapon))    weapon = unew(BINGQI_D("xuedao"));
                if(!objectp(weapon))
                      return "Ѫ�����ڲ��������";  

                command("unwield xue dao");
                weapon->move(me);
                command("emote ����һ��Ѫ����");
                command("wield xinyue dao");
                me->set_temp("xs/xs_job",0);
  
        return "�ã����Ѫ������ȥ�ɣ����Ŷ�ɱ����������������";
}

string ask_zijindao()
{
        object me=this_player() , weapon;

        if ((string)me->query("family/family_name") != "Ѫ����")
                return "����������ˣ���ѵ���ô�ܸ����أ�";

        if ((int)me->query("xs_job") < 1000 )
                return "�Ķ������ж���ѩɽ��������1000���õ�ʵ�ʳɼ������ҿ��\n";

        weapon = present("zijin dao", this_object());
        if(!objectp(weapon))    weapon = unew(BINGQI_D("zijin-dao"));
        if(!objectp(weapon))
                return "�Ͻ����ڲ��������";        

        command("unwield zijin dao");
        weapon->move(me);
        command("emote ����һ���Ͻ𵶡�");
        command("wield xinyue dao");

        return "�ã�����Ͻ�����ȥ�ɣ���ס��Ҫ������ѽ��";
}

void destroying(object obj)
{
	if (!obj) return;
	if (userp(obj))
		command("drop "+obj->parse_command_id_list()[0]);
	else
		destruct(obj);
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return ""+RANK_D->query_respect(me) +"�����Լ�С��ͨ���ɣ�";
	}
	if(me->query(QUESTDIR1+"over" ))
	{
	   command("claw "+me->query("id"));
	   return "�Ǹ����ͷ��С����ôͻȻ��ô�����ˣ�";
	}
	if(!me->query(QUESTDIR1+"start" ))
	{
	   command("say");
	   return "���Ҵ�ѩ���ȥ�ˣ�������Ͷ����ˡ�";
	}
	if(!me->query_temp(QUESTDIR1+"askbaoxiang" ))
	{
	   command("say");
	   command("claw "+me->query("id"));
	   return "�ĸ����ƣ�����˭��";
	}
	if(me->query_temp(QUESTDIR1+"asklaozu"))
	{
	   command("en");
	   return "�Ǹ����ͷ��Ҳ�����Ҳ�������Ӧ�ö����ˣ�";
	}
	command("smash");
	message_vision(HIY"$N��ɫ�԰��ؿ���$n��\n", ob,me);
	command("noshame");
	me->set_temp(QUESTDIR1+"asklaozu",1);
	return "����Ȼ�������ԣ�ֻ�����ֿ�ԣ����Ҵ�ѩ���ȥ�ˣ�������Ͷ����ˡ�";
}



string ask_xuedaojj()
{
	object me,ob;
	int i,j,k; 

	me = this_player();
	if (time()-me->query("quest/xd/xdj/xuedao/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (me->query("family/family_name")!="Ѫ����")
	{
		return "�㲻��Ѫ���ŵ��ӣ�������ǲ��ô��\n";
	}

	if (!me->query("quest/xd/xdj/xuedao/start"))
	{
		return "�㲻Ŭ��ȥѩ����Ϊ��ɱ��Щ���ţ���Ҫ��ɧ���ң���\n";
	}
	if (me->query("quest/xd/xdj/xuedao/pass"))
	{
		me->set("title",HBRED+HIG"Ѫ���󷨴���"NOR);
		return "���Ѿ��⿪Ѫ���ؼ������似�ˣ���\n";
	}
	if (me->query("con")<40)
	{
		
		return "��������ǲ�����ѧ������Ѫ�����ؼ�����\n";
	}

	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return "Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ���ǵմ������ܴ�����߼��书����\n";
	}

		command("say Ѫ���ŵĸ���ȫ���ڵ����ϣ�����ʹ�����ľ���ȴ���ڹ������ϡ�\n");
		command("say ��Щ���ž㶼��д�ڡ�Ѫ���ؼ����Ȿ�书�ؼ��ϡ�\n");

		command("say ���Ȼ���Ŭ�����ڷܣ��Ҿʹ������㣬�����ܷ�������\n");

	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	k=random(me->query("con"));
	if (i>26
	  && j<3
	  && k>40
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N������ת���⣬������Ѩ��Ȼһʹ�����澭������ĩ�Ҿ����Ȼ��ͨ����\n"NOR,me); 
		 message_vision(HIC"\n��Щ����������ǰ$N��������֪���ľ������������ָ���£����Ȼ��������Ȼ��������\n"NOR,me); 

         message_vision(HIY"\n$N�������飬��ת��������Щ�¾�������ת��Ϣ��\n�̲�ס���������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������������������Ѫ�����ռ��ؼ�<<Ѫ����>>���������أ���\n"NOR,me); 
		 command("chat* laugh "+me->query("id"));
		 command("chat* thumb "+me->query("id"));
		 command("chat pat "+me->query("id"));
		 command("chat ��ϲ"+me->query("id")+"�޳�Ѫ�����ռ��ؼ���\n");
		 log_file("quest/xjdxuedao", sprintf("%s(%s) Ѫ���ؼ��ڻ��ͨ�ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�����Ѫ���ؼ��İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ����ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuedao/fail"),
		 i,
		 j,
		 k,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/xdj/xuedao/time",time());
		 me->set("quest/xd/xdj/xuedao/pass",1);
		 me->set("title",HBRED+HIG"Ѫ���󷨴���"NOR);
		 me->set("mytitle/quest/xuddaotitle",HBRED+HIG"Ѫ���󷨴���"NOR);
		 return "��������";
     }
	 else {
	     message_vision(HIG"\n$N�����ɥ�����������˵������������Ѫ���ؼ����ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n����Ѫ���ؼ���������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xdjxuedao", sprintf("%s(%s) ʧ�ܣ�����Ѫ���ؼ���%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ����ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuedao/fail",1),
		 i,
		 j,
		 k,
         me->query("combat_exp"),));        
		 me->add("quest/xd/xdj/xuedao/fail",1);
		 me->set("quest/xd/xdj/xuedao/time",time());
		 me->start_busy(2);
		 return "�������㣬�������Ѽ�ȥ�ˣ�\n";
   }
	
}

string ask_xuesha()
{
	object me,ob;
	int i,j,k; 

	me = this_player();
	if (time()-me->query("quest/xd/xdj/xuesha/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (me->query("family/family_name")!="Ѫ����")
	{
		return "�㲻��Ѫ���ŵ��ӣ�������ǲ��ô��\n";
	}

	if (me->query("quest/xd/xdj/xuesha/pass"))
	{
	//	me->set("title",HBRED+HIG"Ѫ���󷨴���"NOR);
		return "���Ѿ��⿪Ѫ������Ѫɷ�似�ˣ���\n";
	}
	if (me->query_skill("xuedao-jing",1)<350)
	{
		
		return "��Ѫ�����ȼ�����350��ѧ������Ѫɷ����\n";
	}
	if (me->query("PKS")<5)
	{
		return "�����˶�ûɱ����ȥ����ɱ��������������ȣ�����ѧ������Ѫɷ�������书������Ե��\n";

	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return "Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ���ǵմ������ܴ�����߼��书����\n";
	}
	command("say Ѫ���ŵ��ڹ��ǱȽ����ص��书�������������Ȼ����ժ�����ˣ���Ҳ������ذ��\n");
	command("say �����ڴ�ѩ��һս������Ҳ�ܰ���ν�Ľ����Ĵ�����������\n");
	command("say ����ʵ��ҪһЩ��ʶ��������,������˹�����Ȼ���������Է������öԷ����»�����������!\n");
	command("say �㸽���������Ҹ���˵ЩҪ����������Ҫ���ǿ������ԡ�\n");
	command("say ��ס��ɱ���Խ�࣬�����ķ��Ϳھ�Խ���������û��ɱ���ˣ�����������书��Ե��\n");

	command("say ���Ȼ���Ŭ�����ڷܣ��Ҿʹ������㣬�����ܷ�������\n");

	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	k=random(me->query("PKS"));
	if (i>25
	  && j<5
	  && k>20
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N��Ȼ�丣�����飬Ѫ������ת���⣬���϶�ʱ����һ������ĺ�ɫ����\n"NOR,me); 
		 message_vision(HIC"\n$N�����˶��Ե����а��Ϳֲ���\n"NOR,me); 

         message_vision(HIY"\n\n�̲�ס���������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������������������Ѫ������Ѫɷ���������أ���\n"NOR,me); 
		 command("chat* smile "+me->query("id"));
		 command("chat* nip "+me->query("id"));
		 command("chat* pat "+me->query("id"));
		 log_file("quest/xjdxuesha", sprintf("%s(%s) Ѫ����Ѫɷ�ؼ���ͨ�ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�����Ѫɷ�ؼ��İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰɱ��ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuesha/fail"),
		 i,
		 j,
		 k,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/xdj/xuesha/time",time());
		 me->set("quest/xd/xdj/xuesha/pass",1);
		// me->set("title",HBRED+HIG"Ѫ���󷨴���"NOR);
		 return "С�ӣ����²�����Ϊʦ�Ļ�����ʽ�㶼ѧ���ˣ�\n";
     }
	 else {
	     message_vision(HIG"\n$N�����ɥ�����������˵������������Ѫɷ�ؼ����ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n����Ѫɷ�ؼ�����ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xdjxuedao", sprintf("%s(%s) ʧ�ܣ�����Ѫɷ�ؼ���%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰɱ��ֵ��%d����ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuesha/fail",1),
		 i,
		 j,
		 k,
         me->query("combat_exp"),));        
		 me->add("quest/xd/xdj/xuesha/fail",1);
		 me->set("quest/xd/xdj/xuesha/time",time());
		 me->start_busy(2);
		 return "�ⶼ���ᣬ�Ժ��˵�����ҵĵ��ӣ�\n";
   }
	
}
