string s_power(int i)
{
	if( i >= 30 )	return HIW"����"NOR;
	if( i >= 20 )	return HIG"�ܸ�"NOR;	
	if( i >= 10 )	return HIY"����"NOR;		
	return "һ��";
}
/*
string t_power(int t)
{
	if( i >= 150 )	return HIM"��ɫ�����װ(����)"NOR;
	if( i >= 120 )	return HIR"��ɫ�����װ(�߼�)"NOR;	
	if( i >= 100 )	return HIY"��ɫ�����װ(�ܺ�)"NOR;
	if( i >= 80 )	return HIC"��ɫ�����װ(����)"NOR;		
	if( i >= 50 )	return HIW"��ɫ�����װ(һ��)"NOR;		

	return "��ֵһ��";
}
*/

void token_reload()
{
	string str;
	int i,a,d,p,t;
	if(mapp(this_player()->query("token/"+query("id"))))
	{			
		if (i=this_player()->query("token/"+query("id")+"/parry")) 
		{
			set("armor_prop/parry",i);
			str="�мܷ�����";
			set("long",query("long")+" "+this_player()->query("token/"+query("id")+"/desc")+"\n"NOR
			+"\n���"+query("name")+"����������"+s_power(i)+"��"+str+"��\n");
			p=i;

		}	
		if (i=this_player()->query("token/"+query("id")+"/dodge"))
		{
			set("armor_prop/dodge",i);
			str="�����";
			set("long",query("long")+" "+this_player()->query("token/"+query("id")+"/desc")+"\n"NOR
			+"\n���"+query("name")+"����������"+s_power(i)+"��"+str+"��\n");
			d=i;

		}
		if (i=this_player()->query("token/"+query("id")+"/armor"))
		{
			set("armor_prop/armor",i);
			str="���׷�����";
			set("long",query("long")+" "+this_player()->query("token/"+query("id")+"/desc")+"\n"NOR
			+"\n���"+query("name")+"����������"+s_power(i)+"��"+str+"��\n");
			a=i;
		}
		wear();
	}
}

int do_discard(string arg)
{
	object me = this_player();
	if (arg!=query("id"))
      		return notify_fail("��Ҫ����ʲô?\n");
      	
      	write("��Ҫ����"+query("name")+",ȷ����[Y|N]��");
	input_to("confirm_discard",me);
      	return 1;
}

private void confirm_discard(string arg,object me)
{
	if( arg[0]=='y' || arg[0]=='Y' )
	{
		me->delete("token/"+query("id"));
		write("��ж��"+query("name")+"����ض���û��ע��Ľ��䡣\n");
		destruct(this_object());
	}
	else
	{
		write("\n���������"+ query("name")+"��\n");
	}
}

int query_autoload()
{
	return 1;
}

int unequip()
{
	object ob = environment();

	if (ob && userp(ob))
		return notify_fail("������������Ͱ�������(discard)�˰ɡ�\n");

	return ::unequip();
}