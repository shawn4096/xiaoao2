string s_power(int i)
{
	if( i >= 30 )	return HIW"极高"NOR;
	if( i >= 20 )	return HIG"很高"NOR;	
	if( i >= 10 )	return HIY"不错"NOR;		
	return "一般";
}
/*
string t_power(int t)
{
	if( i >= 150 )	return HIM"紫色组合套装(超级)"NOR;
	if( i >= 120 )	return HIR"红色组合套装(高级)"NOR;	
	if( i >= 100 )	return HIY"黄色组合套装(很好)"NOR;
	if( i >= 80 )	return HIC"蓝色组合套装(不错)"NOR;		
	if( i >= 50 )	return HIW"白色组合套装(一般)"NOR;		

	return "不值一提";
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
			str="招架防御力";
			set("long",query("long")+" "+this_player()->query("token/"+query("id")+"/desc")+"\n"NOR
			+"\n这个"+query("name")+"看起来有着"+s_power(i)+"的"+str+"。\n");
			p=i;

		}	
		if (i=this_player()->query("token/"+query("id")+"/dodge"))
		{
			set("armor_prop/dodge",i);
			str="躲避率";
			set("long",query("long")+" "+this_player()->query("token/"+query("id")+"/desc")+"\n"NOR
			+"\n这个"+query("name")+"看起来有着"+s_power(i)+"的"+str+"。\n");
			d=i;

		}
		if (i=this_player()->query("token/"+query("id")+"/armor"))
		{
			set("armor_prop/armor",i);
			str="护甲防御力";
			set("long",query("long")+" "+this_player()->query("token/"+query("id")+"/desc")+"\n"NOR
			+"\n这个"+query("name")+"看起来有着"+s_power(i)+"的"+str+"。\n");
			a=i;
		}
		wear();
	}
}

int do_discard(string arg)
{
	object me = this_player();
	if (arg!=query("id"))
      		return notify_fail("你要丢弃什么?\n");
      	
      	write("你要丢弃"+query("name")+",确定吗？[Y|N]：");
	input_to("confirm_discard",me);
      	return 1;
}

private void confirm_discard(string arg,object me)
{
	if( arg[0]=='y' || arg[0]=='Y' )
	{
		me->delete("token/"+query("id"));
		write("你卸下"+query("name")+"轻轻地丢到没人注意的脚落。\n");
		destruct(this_object());
	}
	else
	{
		write("\n你决定保留"+ query("name")+"。\n");
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
		return notify_fail("如果不想戴了你就把它丢弃(discard)了吧。\n");

	return ::unequip();
}