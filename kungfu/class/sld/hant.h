// hant.h �鰲ͨ
//���Ǿ���
//#include "ansi.h"

int do_huagu()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "������" ){
		command("say �㲻��������������ʿ����������\n");
		return 1;
	}
	if (me->query("family/generation")>2)
	{
		command("say ��Ƕ������ӣ�������������\n");
		return 1;
	}
	if (me->query_skill("huagu-mianzhang",1)<450)
	{
		command("say ��Ļ������Ʋ���450������Ҳѧ���ˣ�\n");
		return 1;
	}    
	if (me->query("quest/sld/hgmz/pass")){
		command("say ���Ѿ�����������⻹������������\n");        	
		return 1;				
	}
	if (me->query("gender")=="Ů��"){
		command("say �������������⹦���ҿ�Ů���޾����ˣ���\n");        	
		return 1;				
	}
	if (time()-me->query("quest/sld/hgmz/time")<86400){
		command("say ��Ҳ̫�ڿ����Ү����\n");        	
		return 1;				
	}
	if (me->is_busy())
	{
		command("say ��Ҳ��æ����������������\n");        	
		return 1;			
	}

		    command("say ��������һ�и���ȫ�����ߵ�֮�ϣ����������Ƶľ�Ҫ���Ƕ���\n");
		    command("say �������ƽ����Ĳ��ǿ죬�����ͣ���Ҫ�����ںݣ�����\n");
			command("say ����С��һ���ĺ�������ģ�������ʺ������񹦵Ĵ��С�\n\n\n");
			me->set_temp("hgmz/askhong",1);
			if (random(me->query("kar"))>25)
			{
				command("say ����������������ˣ���ͽ�����������ҾͰ��⻯�����Ƶľ�Ҫ˵������������Ҫ�����ˣ�\n");
				message_vision(HIR"\n\n$N������������ʦ���鰲ͨ��̹��ڻ������Ƶľ�����\n"NOR,me);
				me->start_busy(999);
				remove_call_out("thinking");
				call_out("thinking",1,me);
				me->delete_temp("hmgz/askhongok",1);
				return 1;

			}else {
				
				command("say ���������鲻�ã������վԶ�㣡\n");
				command("say �������Ÿ�С���˲����������ѻ�\n");

				message_vision(HIR"\n\n$N������������ʦ���鰲ͨ��̹��ڻ������Ƶľ�����\n"NOR,me);
				
				me->add_temp("hgmz/askhong",1);
				if (me->query_temp("hgmz/askhong")>4)
				{
					command("say �����룡\n");
					command("shout "+me->query("name")+"�����С�����������ң�����ҳ��֣�\n");
					message_vision(HIR"\n\n�鰲ͨ�������ԣ�ͻȻ�䲪Ȼ��ŭ��һ�Ž�$N�߳����⡣\n"NOR,me);
					me->move("d/sld/ht");
					me->add_busy(1);
				}

				return 1;
			}
}
//�������� ����
int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
 
  j = 25;
  if(me->query("m-card-vip")) j =  22;
  if(me->query("y-card-vip")) j =  20;
  if(me->query("buyvip"))     j =  17;
  j=random(j);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ���򻯹�����ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huagu")<(30+random(10)))
   {  
	  me->add_temp("canwu_huagu",1);
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
   else if (i>26
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˺���������ڵĻ������Ƶİ��ػ�Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/huagumianzhang", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ����򻯹Ǿ����İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/hgmz/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/hgmz/time",time());
		 me->set("quest/sld/hgmz/pass",1);
		 me->delete_temp("canwu_huagu");
		 me->delete_temp("hgmz");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n���򻯹����ƾ�������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/huagumianzhang", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ��򻯹����ƣ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/hgmz/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/hgmz/fail",1);
		 me->set("quest/sld/hgmz/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_huagu");
		 me->delete_temp("hgmz");
		 return 1;
   }

}
//�����󷨾���

int do_dldf()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "������" ){
		command("say �㲻��������������ʿ����������\n");
		return 1;
	}
	if (me->query_skill("dulong-dafa",1)<500 ){
		command("say ��Ķ����󷨲���500������������\n");
		return 1;
	}
	if (!me->query("quest/sld/dldf/start")){
		command("say ��Ϊ�Ҵ����������������ʲô���ף�\n");
		command("sigh ");
		command("say ֻ�ж�����ս����Ϊ�Ҵ��������º����ͣ����ܻ���ҵ��洫��\n");
		return 1;
	}
	if (me->query("family/generation")>2)
	{
		command("say ��Ƕ������ӣ�������������\n");
		return 1;
	}
	if (me->query_skill("dulong-dafa",1)<450)
	{
		command("say ��Ķ����󷨲���450������Ҳѧ���ˣ�\n");
		return 1;
	}
    if (me->query("quest/sld/dldf/pass")){
		command("say ���Ѿ�����������⻹������������\n");
		me->set("title",HIG"������"+HIB"�����󷨴���"NOR);

		return 1;				
	}
    if (me->query("con")<40){
		command("say ���������ǲ���40���ֿ����˶������ģ���\n");        	
		return 1;				
	}
//	if (me->is_busy())
	//{
		//command("say ��Ҳ��æ����������������\n");        	
		//return 1;			
//	}

	if (time()-me->query("quest/sld/dldf/time")<86400){
		command("say ��Ҳ̫�ڿ����Ү����\n");        	
		return 1;				
	}
		    command("say ��������һ�и���ȫ���ⶾ���󷨵��ڹ�֮�ϣ�����˵�����������̵ĸ�����\n");
		    command("say ��������Ҫ�Զ��������蹦���������ն��ߴﵽ�ڻ��ͨ��\n");
			command("say ����һ���ĺ�������ģ�������ʺ������񹦵Ĵ��У�����Ҫ�мǣ��ⶾ���ڹ�����Ҳ�Ƚ�Σ�ա�\n");
			command("say ���в������ܶ����������м��мǡ�\n\n\n");

			me->set_temp("dldf/askhong",1);
			
			if (random(me->query("kar"))>25)
			{
				command("say ����������������ˣ���ͽ�����������ҾͰ��ⶾ���󷨵ľ�Ҫ˵������������Ҫ�����ˣ�\n");
				message_vision(HIC"\n\n$N������������ʦ���鰲ͨ��̹��ڶ����󷨵ľ�����\n"NOR,me);
				me->start_busy(999);
				remove_call_out("thinking_dldf");
				call_out("thinking_dldf",1,me);
				me->delete_temp("dldf/askhong",1);
				return 1;

			}else {
				
				command("say ���������鲻�ã������վԶ�㣡\n");
				command("say �������Ÿ�С���˲����������ѻ�\n");

				message_vision(HIR"\n\n$N������������ʦ���鰲ͨ��̹��ڶ����󷨵ľ�����\n"NOR,me);
				
				me->add_temp("hgmz/askhong",1);
				if (me->query_temp("hgmz/askhong")>5)
				{
					command("say �����룡\n");
					command("shout "+me->query("name")+"�����С�����������ң�����ҳ��֣�\n");
					message_vision(HIR"\n\n�鰲ͨ�������ԣ�ͻȻ�䲪Ȼ��ŭ��һ�Ž�$N�߳����⡣\n"NOR,me);
					me->move("d/sld/ht");
					me->start_busy(1);
				}

				return 1;
			}
}

int thinking_dldf(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  me->set("quest/sld/dldf/time",time());
  
  j = 25;
  if(me->query("m-card-vip")) j =  23;
  if(me->query("y-card-vip")) j =  20;
  if(me->query("buyvip"))     j =  17;
  j=random(j);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ��������ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_dldf")<(10+random(10)))
   {  
	  me->add_temp("canwu_dldf",1);
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

	  remove_call_out("thinking_dldf");
	  call_out("thinking_dldf",3+random(3), me);

   } 
   else if (i>27
			&& j<2
	   		&& random(me->query("con"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˺���������ڵĶ����󷨵İ��ػ�Ȼ��ͨ����\n"NOR,me); 
		 message_vision(HIG"\n��ϲ������$Nǧ����࣬���ڵó���Ը���⿪�����󷨵��ռ����⣡��\n"NOR,me); 

         log_file("quest/dldf", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ��������󷨵İ��أ���ǰ�������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/dldf/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/dldf/time",time());
		 me->set("quest/sld/dldf/pass",1);
		 me->start_busy(1);
		 me->set("title",HIG"������"+HIR"�����󷨴���"NOR);
		 me->delete_temp("canwu_dldf");
		 me->delete_temp("dldf");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n��������û�����򵽶������ںϵ�����,�����߶�������\n"NOR,me); 
		 me->apply_condition("snake_poison",1);
		 message_vision(HIY"\n�������󷨾�������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/dldf", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ������󷨾�������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/dldf/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/dldf/fail",1);
		 me->set("quest/sld/dldf/time",time());
		 me->start_busy(1);
		 me->delete_temp("canwu_dldf");
		 me->delete_temp("dldf");
		 return 1;
   }

}

/**/
//������֮��������


string do_dulong()
{
	object me,ob;
	int i,j;
	me=this_player();
	if (!me->query("quest/sld/dldf/dulong/start"))
	{
		command("say ����δ�˽������鶯��ʹ֮������Ҳ�״");
		return "��\n";
	}
	if (!me->query_temp("quest/sld/dulong/asksu"))
	{
		command("say ����¸����й�ϵô����");
		return "��\n";
	}

	if (me->query_skill("qusheshu",1)<200)
	{
		command("say ��������Ҫ�ﵽ200��ɽ׶η�����ϰ��\n");
		return "";
	}
	if (me->query_skill("force",1)<450)
	{
		command("say �����ڹ��ﵽ450��ɽ׶η�����ϰ��\n");
		return "";
	}
	if (me->query("family/family_name")!="������")
	{
		command("say �㲢�������̵��ӣ�\n");
		return "";
	}
	if (time()-me->query("quest/sld/dldf/dulong/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�\n");
		return "";
	}
	if (me->query("quest/sld/dldf/dulong/pass"))
	{
		command("say ���Ѿ��⿪��������ˣ�\n");
		return "";
	}
	
	command("consider ");
	command("sigh "+me->query("id"));
	command("say ��Ȼ�Ƿ������������ң��Ҿ͸���˵�°ɣ�\n");
	message_vision(HIY"�鰲ͨ��$N˵������ܲ�����Ȼ����ѵ�߹���������ô��������������򣬿����ǿ���֮�ģ���\n"NOR,me);

	command("say ��������������ɫ֮һ���Ƕ��ڸ��ֶ��ߵ��о���\n");
	command("say ��������һ�������Ҳŷ��֣�����Ҳ�ǿ��Կ��ƣ�������϶����󷨣�����������\n");
	command("say �����ڶ�ս�����н�����ų�������Է�����ʤ����\n");
	command("say ��Ȼ�����������������ֵ�һ�о�����ʽ��������Ҳ�ͻ�����������Ҫ������ѱ��һ����\n");
	command("say ��������Ȥ�Ҿͽ����ž����������㣡\n");
	

	
	if( !objectp(ob=me->query_temp("sld/snake")) 
		||!present("jin she",me))
		return "����Ҫ��ѱ��һ�������߷�����̡�\n";
	  
	if (me->is_busy())
	{
	  command("say ������æµ��!\n");
	  return "";
	}
	me->start_busy(20);
	command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��200�㣬���������û�ʸ�����ҡ�\n\n\n\n");

	if (me->query("party/gongji")<100)
	{
		command("say ������ɹ�������\n");
		return "";
	}
	command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
    command("whisper "+me->query("id"));
	me->add("party/gongji",-100);
	
	i = 25;
		if(me->query("m-card-vip")) i =  22;
		if(me->query("y-card-vip")) i =  20;
		if(me->query("buyvip"))     i =  17;
		i=random(i);
		j=random(me->query("kar"));
		command("say ��������ô��\n");
		command("pat "+me->query("id"));
		if( i<3
			&& me->query("kar")<31
			&& random(me->query_int(1))>35
			&& j > 27 ) 
		{
			tell_object(me,HIC"\n�����˵ĺ鰲ͨ������ָ�㣬�����������Լ�ѱ�߹����е������ĵã����±˴�ӡ�գ������ĵá�\n"NOR);
			tell_object(me,HIG"\n�㰴�պ鰲ͨ��ָ�㣬���Զ�������ʹ�Լ���ѱ�����������޲����⡣\n"NOR);
			tell_object(me,HIB"\n�㷢�����������ڶ�������ʹ֮�£��鶯�쳣��\n"NOR);
			tell_object(me,HIY"\n������ǧ����࣬�������ɶ����󷨶���������\n"NOR);

			me->set("quest/sld/dldf/dulong/pass",1);
			log_file("quest/slddulong", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������󷨶���������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|������ǣ�%d��\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/dulong/fail"),i,j,me->query("kar"),me->query_con(1)) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "��ϲ���ܶ����������ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/slddulong", sprintf("%8s(%8s) ���ܶ���������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/dulong/fail"),i,j,me->query("kar"),me->query_con(1)) );
			
			tell_object(me,HIY"������������ָ�㣬���ǶԶ����������İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/sld/dldf/dulong/fail",1);
			me->set("quest/sld/dldf/dulong/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "�ǳ��ź����ܶ���������ʧ��"+me->query("quest/sld/dldf/dulong/fail")+"�Ρ�\n";
		}

	
}