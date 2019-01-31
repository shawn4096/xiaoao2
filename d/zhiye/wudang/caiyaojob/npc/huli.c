// huli.c

inherit NPC;

void create()
{
        set_name("狐狸", ({ "hu li", "li" }) );
        set("race", "野兽");
        set("age", 5);
        set("long", "一只浑身棕色的狐狸，它正瞪着眼睛看着你。\n");

        set("limbs", ({ "头部", "身体", "前爪", "后爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 5000);

	set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 10);

        setup();
}

void init()
{
  	object me;
  	me=this_player();
  	call_out("huli", 2, me);	
}
void die()
{
       object ob;
       message_vision("$N惨嚎一声，死了！\n", this_object());
       ob = new("/u/bren/test/obj/hulipi");
       ob->move(environment(this_object()));
       destruct(this_object());
}

void huli(object me)
{
    remove_call_out("huli");

               
    if (environment(me) == environment(this_object()))
    {
    message_vision("狐狸看到有人过来了，“嗖——”的一下钻到了旁边的杂草中不见了！\n",me);
    destruct(this_object());
    
    }

return 0;
}