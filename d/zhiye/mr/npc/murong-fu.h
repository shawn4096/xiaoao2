/*
int do_lingwu(string arg)
{
	object me=this_player();
	object who=this_object();
	int i = me->query_skill("douzhuan-xingyi", 1);
    int lv = me->query("max_pot")-100;
	if( !living(who))
		return notify_fail("慕容复现在的状况，看来无法回答你任何问题。\n");

	if ( me->query("family/family_name") != "姑苏慕容")
		return notify_fail("你非我慕容弟子，向我讨教什么啊？\n");

	if (!arg || arg !="douzhuan-xingyi" ){
		message_vision("$N向$n讨教一些关于武学上的疑问。\n", me, who);
		command("dunno "+me->query("id"));
		return 1;
	}
	if (me->is_busy() || me->is_fighting()){
		command("say 你正忙着干别的事情呢，忙完了再说吧。");
		return 1;
	}
	if( me->query("jing") < 10)
		return notify_fail("你太累了，还是休息一会吧。\n");
	if((int)me->query("potential", 1) < 1 )
		return notify_fail("你潜能不够。\n");
	if ( i <= 50 ){
		command("say 你的斗转星移等级不够，还不能从我这里学到什么。");
		return 1;
	}
	write("你向慕容复讨教关于「" + to_chinese(arg) + "」的疑问。\n");
	write(HIC"你听了慕容复的指点，领悟到斗转星移的精髓所在。\n");
	write(HIR"你的[斗转星移]提高到了你目前实战经验限制的最高级别！\n");
    me->set_skill("douzhuan-xingyi", lv);

       if (i >= lv -1)
         {
		command("say 你的实战经验不够，无法领悟到什么。");
		return 1;
	}
        
	return 1;
}*/
string ask_shixibiao()
{
	object me=this_player();
	if (!me->query("quest/天龙八部/复兴天下篇/over"))
	{
		command("你先把天龙八部秘密解完，实力提升了我再告诉你。\n");
		return "想偷懒？没门！";
	}
	
	command("say 好吧，既然如此我就将这段往事告诉你。\n");
	command("say 既然你已经是慕容世家忠实的弟子，说予你听也无妨。\n");
	command("say 我大燕国确实有此世袭表，但此世袭表却不知道所踪。\n");
	command("say 你若有心，我倒是可以提醒你一下，也许你机缘巧合能有新发现也说不定。\n");
	command("say 我曾听我父亲说道，当初我家举家南迁之际，曾在太湖一带遇到一帮土匪。\n");
	command("say 当时一场混战，双方死亡不少，就是在那次混乱中，装世袭表的那个箱子不见所踪。\n");
	command("say 我想应该是流落到那一带，后来我私下打听，那帮土匪好像是铁掌帮乔装所为。\n");
	command("say 我以后有机会一定会找裘千仞算这一笔账。\n");
	me->set_temp("sxb/askfu",1);
	return "神思恍惚，不知道在想什么。只是不断地嘀咕，前一阶段据铁掌帮密探说曾在\n铁掌峰食指峰中曾有人发现过一个包裹。不知道是真是假？\n";

}
string ask_mishi()
{
	object me=this_player();
	object key,wkey;
	if (!me->query("quest/天龙八部/复兴天下篇/over"))
	{
		command("say 你先把天龙八部秘密解完，实力提升了我再告诉你。\n");
		return "想偷懒？没门！";
	}
	
	command("say 好吧，我大燕国有一个地下密室，里面放置了大量的武器装备。\n");
	command("say 既然你已经是慕容世家忠实的弟子，说予你听也无妨。\n");
	command("say 为我大燕国未来复国做准备的，我现在给你一把进去的黑钥匙，你去找找看。\n");
	key=new("d/mr/obj/mrkey");
	key->move(me);
	command("say 这是另外一把白钥匙，是出来时候开门用的，小心收藏好了。\n");
	wkey=new("d/mr/obj/mrkey1");
	wkey->move(me);
	return "凡事都要有耐心，这天下能战胜我慕容山庄的人还没出现呢，好好干！\n";

}
