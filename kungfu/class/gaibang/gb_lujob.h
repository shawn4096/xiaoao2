//By Spiderii@ty ��ʱ�ر�smy.exp����Ū��̫��
// gb_lujob.h
// Lklv 2001.9.28 update change gb_job.c -> gb_lujob.h and rebuild it

string gb_job1()
{
	object me = this_player();

	if(me->query_temp("gb_job1"))
	    return "���ϴε�����û����ɣ�����ô������������¡�";
	command("say �ղ��ҽӵ���������״��ɸ봫�飬���Ĺ�������ʮ�������Ҵ��Ρ�");
	new(__DIR__"obj/gaoji-wenshu")->move(me);
	message_vision("$N��$nһ�Ÿ漱���顣\n", this_object(), me);
	me->set_temp("gb_job1",1);
	return "���ٽ���ݸ漱���齻���߹��ؽ����������������������";
}

string gb_job2()
{
	object me = this_player(), ob = this_object();
	mixed *ob_list;
	int max,i;
	object obj1;

	if( me->query_temp("gb_job2") )
		return "�㲻���Ѿ��ӹ���������";

	ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
		obj1 = ob_list[i];
		if (obj1->query_temp("gb_job2") )
			return "����������Ѿ�����" + obj1->query("name")+"("+capitalize(obj1->query("id"))+")"+"ȥ���ˡ�";
	}

	if( ob->query_temp("gb_job2") )
		return "����������û��ʲô������Ը��㡣";

	if (me->query("job_name") == "���ղ��ϳ�")
		return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

	set_temp("gb_job2",1);
	me->set_temp("gb_job2",1);
	me->apply_condition("gb_job2",40);
	me->apply_condition("job_busy", 10);
	
	command("say �ɹŴ�����Ҵ��������ǣ�ÿ�ζ�������Ϊ����֮����\n");
	command("say �����������������͵Ϯ�������ؽ��������ܶ�ʧ�ܡ�\n");
	command("say ǰ���챾����Ӵ�̽�������Ǳ���һ�����£������վ����ɹű����ؿ��顣\n");
	return "��Ӹô�����ȥ���Ż��յ��ɹ����֣��Խ�������֮Χ��";
}

string gb_job3()
{
	object me = this_player(), ob = this_object();
	mixed *ob_list;
	int max, i, j;
	object obj1;

	if( me->query_temp("gb_job3") )
	      return "�㲻���Ѿ��ӹ���������";

	if( me->query("job_name") == "��ɱ��Ԫ˧")
	      return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

	if( !wizardp(me) && me->query_condition("job_busy"))
	      return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

	ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
		obj1 = ob_list[i];
		if (obj1->query_temp("gb_job3") )
			return "����������Ѿ�����" + obj1->query("name")+"("+capitalize(obj1->query("id"))+")"+"ȥ���ˡ�";
	}

	for (j=1;j<6;j++)
		load_object("/d/gb/zhongjun"+j);
	j = sizeof(children("/d/gb/npc/yuanbing-shiwei"));

	if ( j < 6 )
		return "�ɹŴ���ʱû�ҵ��ټ����Ȼ������ɡ�";

	if( ob->query_temp("gb_job3") )
		return "����������û��ʲô������Ը��㡣";

	GIFT_D->check_count(me,this_object(),"��ɱ");

	command("say �ɹŴ��ɸ����ճ�����ʾ�����ʮ�򣬱�����·����ͼ����������\n");
	command("say Ϊ��֮�ƣ�ֻ��Ѱ����ɱ�ɹŴ󽫣�������ʹ�ɹŴ����Χ������\n");

	set_temp("gb_job3",1);
	me->set_temp("gb_job3",1);
	me->apply_condition("gb_job3", 50);
	me->apply_condition("job_busy", 10);
	command("say ��ؤ������״���Ѿ�Ǳ���ɹž��У����ȥ�������ŵ�����\n");
	return  "�����������ɹŴ�Ӫ���Ż���ɱ�ɹŴ󺹡�";
}

#define DEBUG_MODE 0

string smy_job()
{
	object me = this_player(), ob = this_object();
	int max,i;
	int totalexp=0, maxexp, minexp;//��ֹexp���̫��
	object obj1;
	object *ob_list;
	object ob2;
	object fbroom;
	object *team;
	
	
	team = me->query_team();
	//��������ģʽ
	if (team){		
		
		
		if (team[0] != me) {		
		return "ֻ�ж���������ܽ�����";
	    }
		if (sizeof(team) > 2 ){
		 return "��ȥ�ж������˶࣬�������ԡ�";
		}
		
		maxexp=minexp=team[0]->query("combat_exp");
		
		
		for (i=0;i<sizeof(team);i++){
			
			
		totalexp = totalexp + team[i]->query("combat_exp");
		
		if(team[i]->query("combat_exp") > maxexp) {
			maxexp=team[i]->query("combat_exp");
			//maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp") < minexp)
			  minexp=team[i]->query("combat_exp");		
			
			
		if (!team[i]){
			return "��Ķ�����������⣬���ɢ�������齨��";
		}
		
         if (!present(team[i])){			
			return "�ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����";
		}
        
         if ((int)team[i]->query("shen")<0) 
			return "��Ķ������м���С�ˣ��Ҳ����İ�������񽻸��㡣";		 
   
		if( team[i]->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		{			
			return "���������ڽ���֮�У����ǻ����ȴ����������������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="������Ħ��") //added by tangfeng ��quest��ͻ
		{			
			return "���Ƕ������˸�������Ħ�£����ǻ����ȵ����������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="�����ɹ�����" )
		return "��������ɹ�������������";
		
		if (team[i]->query_condition("job_busy") ||team[i]->query_condition("gb_job_busy"))
		{			
			return "���Ƕ������˸�����������Ҫ��Ϣ��";
		}
		if (team[i]->query_condition("killer")) 
			return "��Ķ������б��ٸ�ͨ�����ˡ�";
		
		
		
		if (me == team[i]) continue;
/*
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
		return "�㻹�ǽ�"+team[i]->query("name")+"���������˰ɡ�;
		}*/

	}
      if((maxexp-minexp) > 2000000){
			return "��ȥ����������ҿ���λ��Ա�������ƺ��޴�������";			
		}	

		
	}  //���
	
	//����
	
	
//	if (!wizardp(me))	
//              return "��ʱ�ر�,������������֪ͨ!";
	if ( me->query_temp("smy_job") )
		return "�㲻���Ѿ��ӹ���������";
	
	if (me->query("job_name")=="������Ħ��")
		return "������꿹����Ħ�����񣬻���ЪЪ�ɡ�";
	
	if ((me->query("job_name")=="�´�����")|| me->query_condition("was_busy"))
		return "��������´��������񣬻���ЪЪ�ɡ�";
	
	if ((me->query("job_name")=="�����ɹ�����")|| me->query_condition("was_busy"))
		return "������꿹���ɹ��������񣬻���ЪЪ�ɡ�";
	//if ( me->query("job_name","") )
		//return "�㲻���Ѿ��ӹ���������";
	/*
	//���ﲻ���ж�
	ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
		obj1 = ob_list[i];
		if (obj1->query_temp("smy_job") )
		return "����������Ѿ�����" + obj1->query("name")
		+"("+capitalize(obj1->query("id"))+")"+"ȥ���ˡ�";
	}
	*/
//����
	if( !wizardp(me) && !DEBUG_MODE ) {
	if ( me->query_condition("job_busy") || me->query_condition("gb_job_busy"))
		return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

	if (me->query("job_name") == "������Ħ��")
		return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";
		
	
	}

	ob2 = new("/clone/npc/zhong-shentong");
	if( ob2 ){
		destruct(ob2);
	}
		
	//GIFT_D->check_count(me,this_object(),"��Ħ��");
			
	command("say �ҸղŽӵ���������״��ɸ봫�飬����һƷ����ǲ�������ֶ�����\n" );

	//set_temp("smy_job",1);

	// ������Ϣ
	me->set_temp("smy_job/asked",1);
	me->apply_condition("job_busy", 30);
	command("say ��Ħ����������ʿ�����ıؾ�֮�أ����ٴ�������������������ɱ��\n");	
	me->apply_condition("smy_job", 10);
	
	
	
	fbroom= new("/u/anger/silk3fb");
		fbroom->set("backroom","/d/xingxiu/silk3");//����·��
         fbroom->set("leader",me);//����ӳ�		
		me->set_temp("fbroom",fbroom);//��¼�������䣬��Ϊcond���ж�����
        me->set("job_name", "������Ħ��");     
        command("say ʱ����������õص������ǹ�ȥ��\n");
	    
		//����Ҫ��team ѭ������		
		
	if (team){
		
		me->set_temp("smy_job/team",team);//��¼����
		
		for (i=0;i<sizeof(team);i++){
			team[i]->set("job_name", "������Ħ��");
			message_vision(HIC"$Nһ���㱣���ϸһ��ȴ���ѵ�����Ħ�¡�\n"NOR,team[i]);
			team[i]->move(fbroom);
		}		
	}
    else 
	{
		message_vision(HIC"$Nһ���㱣���ϸһ��ȴ���ѵ�����Ħ�¡�\n"NOR,me);
		me->move(fbroom);
	}		
		
		
		
		

	return "������ʿ�в������֣��������ӣ������󷨣��Բ���ȫ���м��мǡ�";
}
