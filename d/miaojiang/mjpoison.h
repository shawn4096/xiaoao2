void init() 
{
	object ob=this_player();
	
	if (interactive(ob) 
	 && !ob->query_temp("wdj/解毒一")
	 && !ob->query("hmy/poison")
	 //&& ob->query("family/family_name")!="日月神教"
	 && userp(ob)
	 && !ob->query_skill("jiuyang-shengong"))
		ob->add_condition("man_poison", 1);
}
