// zuo.h
// Lklv creat at 2001.10.19

string do_cancel()
{
	object me;
	int exp, i;

	me = this_player();
	exp = me->query("combat_exp");

	if(!me->query_temp("quest") || me->query_temp("quest/family") != "��ɽ��")
		return "��û�������񣬺�������ʲô��";

	me->add("combat_exp",-(20+random(50)));
	if(exp > 500000){
	      me->add("combat_exp",-(30+random(40)));
	}
	i = 40 - me->query_condition("job_busy");
	if ( i >= 9 )
		me->apply_condition("job_busy", 1);
	else
		me->apply_condition("job_busy", 9 - i);
	me->delete_temp("songshan_job");
	me->delete_temp("quest");
	return "��Ȼ��ɲ���Ҳû��ϵ����ȥ�̿������ɣ��Ժ�����Ϊ���ǵĲ��ɴ�Ƴ�����";
}

string do_ask()
{
	object me, ob;
	string type, t;
	mapping quest;

	me = this_player();
	ob = this_object();

	if(ob->is_busy()) return "����æ���أ���ȵȡ�";
	

	if(me->query("combat_exp") > 4000000)
		return "��Ĺ�����ô�ߣ������������ˡ�";

	if( me->query("combat_exp") < 100000
	 || me->query("shen") > -1000)
		return RANK_D->query_respect(ob)+"�ҿ����ֽ�ɢ�����ж��ٻ����ټ��������������ܷ�������ȥ������أ�";

	if( me->query("job_name") == "��ɽ����")
		return "�ţ�����������˼�����ɴ�ƣ������š�";

	if( me->query_temp("quest/id")&& me->query_temp("songshan_job"))
		return "��������ȥ"+HIY+me->query_temp("quest/place")+CYN+me->query_temp("quest/type")+HIG+me->query_temp("quest/name")+CYN+"������ô�������";

	if( me->query_condition("job_busy"))
		return "�ţ�������æ�������š�";

	type = random(2)?"��":"ɱ";

	// get a random npc from TASK_D.
	if(!mapp(quest= TASK_D->get_quest(me, 0, type, "��ɽ��")))
		return "�ţ�����������˼�����ɴ�ƣ������š�";

	me->set_temp("quest", quest);
	me->apply_condition("job_busy", 40);
	t = TASK_D->get_time(quest["time"]);   // get time limit.

	me->set_temp("songshan_job", 1);
	if(type == "ɱ"){
		command("grin");
		command("say �������ˣ��е��ӻر�"HIR+quest["name"]+CYN"���˶�����������֮�����������ô����");
		return "�ٺ٣�����"HIY+quest["place"]+CYN"һ������ȥ����ɱ�ˣ������"+t+CYN"֮ǰ��������ʬ��ϻ�����\n";
	}
	else{
		command("nod");
		command("say ���ˣ�"HIG+quest["name"]+CYN"���ҽ��鲻���������������������֮�¼�ֱ���練�ơ�");
		return "��ʹ�����ȥ"HIY+quest["place"]+CYN"�������������"+t+CYN"֮ǰ�ϻ�����";
	}
}

int accept_object(object who, object ob,object me)
{
       int type,count,exp,pot;
       me=this_object();

       // check job.

       if( who->query_temp("quest/family") != "��ɽ��")
		    return 0;

       type = TASK_D->is_target(ob, who);
       switch (type){
	    case 0: command("say ���ø�"+ob->name()+"���Ҹ��");
		    return 0;
	    case -1:command("say Ү���������㲻ȥ����ɱ�˶���ȥ�ˣ�������");
		    return 0;
	    case -2:command("say �ٺ٣�˭����ȥ��ɱ���ˣ���ֱ�Ǹ�����ɽ��Ĩ�ڣ�");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -3:command("say �ţ���ô�òŰ��꣬���ʲôȥ�ˣ����ҹ�һ��ȥ��");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -4:command("say Ŷ�����Ǹ�ͬ��ͬ�Ե��ˣ�������ù�ɣ�");
		    return 0;
	    default:command("haha");
		    command("say �ã��ã�����²����ǿ�����ӡ�");
		    message_vision("\n$N��$n����һЩ��ѧ�ϵ����ѣ�$n������˼�ص���ͷ��\n",me, who);
		    // give rewards.
		    TASK_D->give_reward(who, who->query_temp("quest"), -1, ABS(me->query("job_time/��ɽ")/100) ,this_object(),"��ɽ" );

	//who->add("job_time/��ɽ", 1);
	//GIFT_D->check_count(who,this_object(),"��ɽ");
	
	who->delete_temp("songshan_job");
	count = who->query("job_time/��ɽ");
	if (count<1) count=1;
	pot= who->query_temp("quest/pot_reward");
	exp= who->query_temp("quest/exp_reward");
	who->delete_temp("quest");
	if (random(who->query("job_time/��ɽ"))>800 && random(who->query("kar"))>25 && !who->query("quest/ss/dichuan")&& who->query("family/family_name")=="��ɽ��")
	{
				message_vision("$N��"+who->query("job_time/��ɽ")+"����ɽ���������л�����������Ͽɣ����㵱�����ĵ��ӿ�����\n",who);
				who->set("title",YEL"���������մ�����"NOR);
				who->set("quest/ss/dichuan",1);
	}
    if (me->query("quest/ss/dichuan"))
	{
				me->set("title",YEL"���������մ�����"NOR);
	}
	log_file("job/songshan",sprintf("%8s%-10s��%4d����ɽɱ��������%3d�㾭�飬%2d��Ǳ�ܣ����飺%d\n",
	who->name(),"("+who->query("id")+")",count,exp,pot,who->query("combat_exp")),who);
	who->set("job_name", "��ɽ����");
	who->clear_condition("job_busy");
	call_out("destroy", 1, ob);
	return 1;
	    }
      return 1;
}

void destroy(object ob)
{
	destruct(ob);
}
//�����ص�--���
string ask_hb()
{
	object me = this_player();

	if (!me->query_temp("hbzq/askzuo"))
		return "ʲô����Ǹ���ѽ����";
	if (random(2)==1)
		return "��������ص���Ҳ���Ǻ������";
	me->set_temp("ss/hb_1",1);
		return "��ŵص����һ��Ͽ�ȸ���������ص���ʵ���벻�����ˡ�\n�����Ҽǵú��������ʱ��ʦ������ѧ�������޷����ұ��䣬��ʧ�ְ����������޴���ɽ�£�\n";
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("sword/guanri-jian")))) {
		ob->move(this_object());
		command("wield guanri qin");
	}
}

string ask_grj()
{
	object me=this_player() , weapon;

	if (me->query("family/master_name") != "������")
		return 0;
	weapon = present("guanri jian", this_object());
	if (!me->query("quest/ss/dichuan"))
	{
		command("say �㲻���ҵĵմ����ӣ�ΪʲôҪ���㣿");
		return "�ߣ�";
	}
	if (!objectp(weapon))
		return "���ս��Ѿ�����ʦ��������,���ڲ��������";
	command("unwield guanri jian");
	command("give guanri jian to " + me->query("id"));
	return "����ս��͸����ˣ����Ҫ���Ʊ��ܺã�";
}

string ask_times()
{
	object me = this_player();
	int i;

	if(!intp(i = me->query("job_time/��ɽ")))
		return "�����С�쵰����������ˣ�����ɱ���ˣ���ƭ�ң�";
	message_vision("$N����$n�����룬˵������Ŀǰ�Ѽǹ�" + chinese_number(i) + "�Ρ�\n", this_object(),me);
	return "����ɽ�����ͷ�����������Ŭ���ɣ�";
}

int do_hssb()
{
	object me = this_player();
	if (me->query("family/family_name")!="��ɽ��")
	  return notify_fail("�㲻������ɽ�ɵ��ӣ��������������");
	if (!me->query("quest/ss/dichuan"))
	  return notify_fail("�㲻������ɽ���״����ĵ��ӣ��������������");
	
	if (me->query("quest/ssjf/jueji/pass"))
	   return notify_fail("���Ѿ�������ɽ���������洫���ѵ�û������ǲ������ô����");
	if( time()-me->query("quest/ss/ssjf/jueji/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("songshan-jian",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�Ľ���û�д�ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�\n");
		return 1;
	}
	if(me->query("int")<40)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ��������������»�������������������������������40���������ҡ�\n");
		return 1;
	}
	message_vision(HIC"$N����$n�����룬˵�������뵱�����������ɻ��ˣ�ħ��ʮ����ս��ɽ����һս\n"+
		"��Ϊ���ң�ħ��ʮ����������ɥ��ɽ�����䲻�������������ɺ���Ҳ��ʧ������\n"+
		"�Ҵ���ɽҲ���ڴ�ս�������������䣬ʹ�����ɾ���������Ȼ��ȱ��ȫ���ܶ���ʽ\n"+
		"������ΪʦҲ�������ˣ��������ģ���ȥ��ɽʯ�ڿ����Ƿ��д˻�Ե����\n"NOR, me);
	me->set_temp("hssb/juejiasked",1);
	return 1;
}

int do_jueji() 
{
	object me = this_player();
	
	if(this_object()->is_fighting()) return 0;
	if(me->query("family/family_name")!="��ɽ��")
	{
		command("heng "+me->query_id());
		command("say �����������ʲô��ϵ���Ͻ����ҹ���");
		return 1;
	}
	
	if(me->is_busy())
	{
		command("heng "+me->query_id());
		command("say �����ë�꼱�٣�������������ž������⣿");
		return 1;
	}
	if(me->query("quest/ss/ssjf/jueji/pass"))
	{
		command("heng "+me->query_id());
		command("say ���Ѿ�����ɽ�����ڻ��ͨ������ǲ������ô��");
		return 1;
	}
	if(me->query("quest/ss/ssjf/jueji/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	
	if (!me->query("quest/ss/ssjf/jueji/hssb"))
	{
	   command("say ��������ȥ��ɽʯ�ڹ�Ħѧϰ���Ž����İ���ô����Ϊ��͵��û�кú��о�һ����\n");
	   return 1;
	}
	message_vision(HIC"$N��$n����й���ɽ�����������ռ����\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	
	if( time()-me->query("quest/ss/ssjf/jueji/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("songshan-jian",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�Ľ���û�д�ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�\n");
		return 1;
	}
    
	me->set("quest/ss/ssjf/jueji/time",time());
	me->set("quest/ss/ssjf/jueji/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("think ");
	command("consider ");
	command("say ԭ���������ӵĽ�֣�\n");
	command("say ��ɽ�������ϴ�����ʧ̫�࣬����������ڷܵķ��Ͼͽ������������ɽ��������˵����������������û����������ˡ�");
    command("say ͽ���������о�������Ϊʦ������Ѫ���ã���ѧϰ��һ��Ҫ�ô˾�������Щα���Ӻ�ħ�̽�ͽ������ȫɱ�ˡ�");
	command("whisper "+me->query("id"));
	
	command("smile "+me->query("id"));
	me->start_busy(999);
	remove_call_out("think_ssjf");
	call_out("think_ssjf",1,me);
	return 1;
}

int think_ssjf(object me)
{
	//object me=this_player();
    int i,j;
	//i=random(20);
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);

	if(me->query_temp("canwu_ssjfjj")<(10+random(5)))
    {  
	  me->add_temp("canwu_ssjfjj",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ���ʽ�˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;
	  }     

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  //remove_call_out("think_ssjf");
	  call_out("think_ssjf",3+random(3), me);
	  return 1;

   } 
	else if( i<4
		&& random(me->query("int"))>40
		&& random(me->query("kar"))>25)
	{
		tell_object(me,HIG"\n�㰴����������ָ�㣬����ڻ�ɽʯ�����ã�����ɽ�����ռ������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIC"\n��������������ڵ���ʽ��ͷ��ʼ������һ·�����������������硣Խ��Խ�Ǵ��졣\n"NOR);
        tell_object(me,HIR"\n��Ȼ�䣬�����һ������ǰ�������Ҳ�벻���׵������Ȼ���Ȼ��ͨ���̲�ס������Ц.\n"NOR);		
		
		command("look "+me->query("id"));
		command("chat "+"�������������Ҵ���ɽ��������һ���ܳ��ĵ��ӣ�ͳһ���ֿ����ֶ���Щ���գ�");
		command("chat*haha "+me->query("id"));
        command("chat*pat "+me->query("id"));
		command("chat "+"��ͽ�����úøɣ��Ժ�������֮λ��������ˡ�");
		
		me->set("quest/ss/ssjf/jueji/pass",1);
		me->set("title",HIC"��ɽ��"+HIY"��ɽ��������"NOR);
		me->set("quest/ss/ssjf/jueji/time",time());
		log_file("quest/ssjfjj", sprintf("�ɹ���%8s(%8s) ʧ��%d�κ󣬳���������ɽ���ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );
		me->delete_temp("canwu_ssjfjj");
		me->delete_temp("hssb");

	}
	else
	{
		command("heng "+me->query("id"));
		tell_object(me,HIY"��������������ָ�㣬��Ȼ��������ɽ������������ʽ�����Ƕ���ɽ��������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/ssjfjj", sprintf("ʧ�ܣ�%8s(%8s) ��ɽ��������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );
		me->set("quest/ss/ssjf/jueji/time",time());
		me->add("quest/ss/ssjf/jueji/fail",1);
		me->delete_temp("canwu_ssjfjj");
		me->delete_temp("hssb");
	}
	me->start_busy(1);
	return 1;

}

int do_chaozong()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(2);
	if (me->query("family/family_name") != "��ɽ��" ){
		command("say �㲻������ɽ������ʿ����������\n");
		return 1;
	}
	if (me->query_skill("songshan-jian",1) < 300){
		command("say ����ɽ������300������������\n");
		return 1;
	}
	if (!me->query("quest/ss/dichuan")){
		command("say ������ɺ��ĵ��ӣ�����ȥ�úð�Ϊ���������ɴ��ȥ���뼸���������ɣ�\n");
		return 1;
	}
	if (me->query_skill("hanbing-zhenqi",1) < 300){
		command("say �㺮����������300������������\n");
		return 1;
	}
	/*
	if (me->is_busy())
	{
		command("say ��̫æ�ˣ�\n");
		return 1;
	}
	*/
	if (me->query("family/master_id")!="zuo lengchan"||me->query("family/master_name")!="������")
	{
		command("say �Ҽǵ�û��������Ӱ���\n");
		return 1;
	}
    if (me->query("quest/ss/ssj/chaozong/pass")){
		command("say ���Ѿ������������,������������������\n");        	
		return 1;				
	}
	
	if (time()-me->query("quest/ss/ssj/chaozong/time")<86400){
		command("say ��Ҳ̫�ڿ����Ү����\n");        	
		return 1;				
	}
	command("say ��ɽ���������������ɾ�������������ɽ����������֮�У�����Ȼ�Ķ������ơ�\n");
	command("say ��Ȼ�Ҵ���ɽ���������ɧ����������˵����ƫ���Ե������\n");
	command("say �����������ھ�����ǫ����չʾ�Ҵ���ɽ�İ�����������������\n\n\n");
			//me->set_temp("chaozong/askzuo",1);
			
	command("say ����������������ˣ���ͽ�����������ҾͰ����������ڵľ�Ҫ˵������������Ҫ�����ˣ�\n");
	message_vision(HIR"\n\n$N������������ʦ����̹����������ڵľ�����\n"NOR,me);
	me->start_busy(999);
	remove_call_out("thinking");
	call_out("thinking",1,me);
			//	me->delete_temp("chaozong/ask",1);
	return 1;

}

int thinking(object me)
{
  int i,j,k; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);

  k = 20;
  if(me->query("m-card-vip")) k =  18;
  if(me->query("y-card-vip")) k =  15;
  if(me->query("buyvip"))     k =  10;
  j=random(k);

  me->set("quest/ss/ssj/chaozong/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ������������ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_chaozong")<(10+random(5)))
   {  
	  me->add_temp("canwu_chaozong",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=26
			&& j<5
			&& me->query("kar")<31)
 	{         
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N�����������������������������ڵİ��أ���ɽ������Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/ssjchaozong", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ������������ڵİ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/ssj/chaozong/fail"),
		 i,
		 j,
         me->query("combat_exp")));
		 me->start_busy(1);
		 me->set("quest/ss/ssj/chaozong/time",time());
		 me->set("quest/ss/ssj/chaozong/pass",1);
		 me->delete_temp("canwu_chaozong");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n�����������ھ�������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/ssjchaozong", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ����������ڣ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/ssj/chaozong/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/ss/ssj/chaozong/fail",1);
		 me->set("quest/ss/ssj/chaozong/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_chaozong");
		 return 1;
   }

}