// yangguo.h ��� �������

//��Ȼ������
//ȥ�����о���ʷ���ֵܣ�
//Ѱ����������ó��֣����Ҫ��Ѱ���ܲ�ͨ
//�ٻ���Ѱ���ܲ�ͨ,��ʼ���,�ֳ�����



int thinking(object me)
{
  int i,j,s,total,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(20);
    j = 25;
    if(me->query("m-card-vip")) j =  23;
    if(me->query("y-card-vip")) j =  20;
    if(me->query("buyvip"))     j =  17;
	//��Ĺ�ɵ���ƫ��
	if (me->query("family/family_name")=="��Ĺ��")
	     s=random(j-3);
	else s= random(j);
 
  
  total=random(me->query("int")+me->query("str")+me->query("con")+me->query("dex"));
  t=random(me->query("int"));
  me->set("quest/xtjf/time",time());
  
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
  if(me->query_temp("canwu_xtjf")<(10+random(10)))
   {  
	  me->add_temp("canwu_xtjf",1);
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

	  //remove_call_out("thinking");

	  call_out("thinking",3+random(3), me);

   } 
   else if (i>28
			&& s<2
			&& total>120
			&& t>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N����������������������������ڵ����������Ŀھ����أ���\n"NOR,me); 
         log_file("quest/xtjf", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ������������������İ��أ���ǰ����ֵ��%d,��ǰ���ֵs��%d,��ǰ���飺%d,��ǰ�����ԣ�%d,��ǰ���ԣ�%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xtjf/fail"),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));

		 me->set("quest/xtjf/time",time());
		 me->set("quest/xtjf/pass",1);
		 me->delete_temp("canwu_xtjf");
		 me->delete_temp("xtjf");

		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵����������������������������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n��������������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xtjf", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ���������������ǰ����ֵ��%d,��ǰ���ֵs��%d,��ǰ���飺%d��,��ǰ�����ԣ�%d,��ǰ���ԣ�%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xtjf/fail",1),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));        
		 me->add("quest/xtjf/fail",1);
		 me->set("quest/xtjf/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_xtjf");
		 me->delete_temp("xtjf");
		 return 1;
   }

}

int anran_think(object me)
{
  int i,j,s,total,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(20);
    j = 25;
    if(me->query("m-card-vip")) j =  23;
    if(me->query("y-card-vip")) j =  20;
    if(me->query("buyvip"))     j =  17;
	//��Ĺ�ɵ���ƫ��
	if (me->query("family/family_name")=="��Ĺ��")
	     s=random(j-3);
	else s= random(j);
 
  
  total=random(me->query("int")+me->query("str")+me->query("con")+me->query("dex"));
  t=random(me->query("str"));
  me->set("quest/anran/time",time());
 
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
  if(me->query_temp("canwu_anran")<(10+random(10)))
   {  
	  me->add_temp("canwu_anran",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ��������Ľ���������������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
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

	//  remove_call_out("anran_think");
	  call_out("anran_think",3+random(3), me);

   } 
   else if (i>28
			&& s<2
			&& total>120
			&& t>40
			&& me->query("kar")<31)
 	{ 
         me->delete_temp("canwu_anran");
         me->start_busy(3);     
         message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N����������������������������ڵ���Ȼ�����ƵĿھ����أ���\n"NOR,me); 
		 command("chat ��ϲ"+me->query("name")+"������Ȼ�����ƾ�����\n");
		 command("chat ��Ȼ�����ƽ����ֽ�����");
         log_file("quest/anranzhang", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������Ȼ�ƾ����İ��أ���ǰ����ֵ��%d,��ǰ���ֵs��%d,��ǰ���飺%d,��ǰ�����ԣ�%d,��ǰ���ԣ�%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/anran/fail"),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));

		 me->set("quest/anran/time",time());
		 me->set("quest/anran/pass",1);
		 me->set_skill("anran-zhang",11);
		 message_vision(HIC"\n��ġ���Ȼ�����ơ������ˣ���\n"NOR,me); 
		 me->delete_temp("canwu_anran");
		 me->delete_temp("anran");
		 me->start_busy();
		 return 1;
     }
	  else {
	     message_vision(HIG"\n\n$N��̾һ�������������˵�������������������Ȼ�Ʒ����ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n\n������Ȼ�����ƾ�������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/anranzhang", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�����Ȼ�Ʒ�����ǰ����ֵ��%d,��ǰ���ֵs��%d,��ǰ���飺%d��,��ǰ�����ԣ�%d,��ǰ���ԣ�%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/anran/fail",1),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));        
		 me->add("quest/anran/fail",1);
		 me->set("quest/anran/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_anran");
		 me->delete_temp("anran");
		 return 1;
   }

}