.class public final Lcom/capcom/zombiecafeandroid/DebugMenuItemClickListener;
.super Ljava/lang/Object;
.implements Landroid/content/DialogInterface$OnClickListener;


# direct methods
.method public constructor <init>()V
    .locals 0

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onClick(Landroid/content/DialogInterface;I)V
    .locals 1

    packed-switch p2, :pswitch_data_0

    :goto_0
    return-void

    :pswitch_0
    const/4 v0, 0x1

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->PurchaseAndroidToxin(I)V

    goto :goto_0

    :pswitch_1
    const/16 v0, 0x3e7

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->DebugSetToxin(I)V

    goto :goto_0

    :pswitch_2
    const/4 v0, 0x1

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->DebugAddMoney(I)V

    goto :goto_0

    :pswitch_3
    const/16 v0, 0x2710

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->DebugAddMoney(I)V

    goto :goto_0

    :pswitch_4
    const v0, 0xf423f

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->DebugAddMoney(I)V

    goto :goto_0

    :pswitch_5
    const/16 v0, 0x2710

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->DebugAddXp(I)V

    goto :goto_0

    :pswitch_6
    const v0, 0xf423f

    invoke-static {v0}, Lcom/capcom/zombiecafeandroid/ZombieCafeAndroid;->DebugSetXp(I)V

    goto :goto_0

    :pswitch_data_0
    .packed-switch 0x0
        :pswitch_0
        :pswitch_1
        :pswitch_2
        :pswitch_3
        :pswitch_4
        :pswitch_5
        :pswitch_6
    .end packed-switch
.end method
