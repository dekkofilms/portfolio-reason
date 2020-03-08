let drawerWidth = "700px";

[%mui.withStyles
  "Styles"({
    drawer: ReactDOMRe.Style.make(
      ~width=drawerWidth,
      ~flexShrink="0",
      (),
    ),
    drawerPaper: ReactDOMRe.Style.make(
      ~width=drawerWidth,
      ~position="relative",
      (),
    ),
    divider: ReactDOMRe.Style.make(
      ~margin="60px 0px",
      (),
    ),
    rightButton: ReactDOMRe.Style.make(
      ~position="absolute",
      ~top="30px",
      ~right="0px",
      ~color="red",
      ~margin="60px 0px",
      (),
    ),
    learnMore: ReactDOMRe.Style.make(
      ~position="absolute",
      ~bottom="30px",
      ~left="48px",
      ~color="red",
      (),
    ),
  })
];

[@react.component]
let make = (~openLeft, ~handleLeftDrawerClose) => {
  MaterialUi.(
    <Styles>
    ...{classes =>
      <Drawer
        className={classes.drawer}
        variant=`Persistent
        anchor=`Left
        open_={openLeft}
        classes=[
          Paper(
            classes.drawerPaper,
          ),
        ]
      >
        <Grid
          style={ReactDOMRe.Style.make(
              ~padding="48px",
              ~height="100%",
              (),
          )}
          container=true
          alignContent=`Center
          alignItems=`Center
        >
          <Button onClick={handleLeftDrawerClose} className={classes.rightButton}>
            <MscharleyBsMaterialUiIcons.Close.Outlined />
          </Button>
          <Grid item=true>
            <Typography variant=`H6>"Three words that describe me"->React.string</Typography>
            <Typography style={ReactDOMRe.Style.make(~lineHeight="1", ())} variant=`H2>"Husband, Engineer, Creative"->React.string</Typography>
            <Divider className={classes.divider} variant=`Middle />
            <Typography variant=`Body1 align=`Center>"dekkofilms@gmail.com"->React.string</Typography>
          </Grid>
          <div className={classes.learnMore}>
            <Typography
              variant=`Body2
              style={ReactDOMRe.Style.make(
                  ~display="flex",
                  ~alignItems="center",
                  ~justifyContent="center",
                  (),
              )}
            >
            "Learn more"->React.string
            <MscharleyBsMaterialUiIcons.ExpandMore.Outlined />
            </Typography>
          </div>
        </Grid>
      </Drawer>
    }
  </Styles>
  )
};

let default = make;
