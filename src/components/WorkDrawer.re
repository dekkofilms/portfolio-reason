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
let make = (~openRight, ~handleRightDrawerClose) => {
  MaterialUi.(
    <Styles>
    ...{classes =>
      <Drawer
        className={classes.drawer}
        variant=`Persistent
        anchor=`Right
        open_={openRight}
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
          <Button onClick={handleRightDrawerClose} className={classes.rightButton}>
            <MscharleyBsMaterialUiIcons.Close.Outlined />
          </Button>
          <Grid item=true>
            <Typography variant=`H6>"Work"->React.string</Typography>
            <Typography style={ReactDOMRe.Style.make(~lineHeight="1", ())} variant=`H2>"Some of the technologies I work with..."->React.string</Typography>
            <Divider className={classes.divider} variant=`Middle />
            <Typography variant=`Body1 align=`Center>"NodeJS, SQL, MongoDB, AMQP, Moleculer, C++, ReasonML, GraphQL, Microservices, SOA, Redis, REST, Docker, Git, System Design, CI/CD, Heroku, and a passion to learn more..."->React.string</Typography>
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
            "See more of my work below"->React.string
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
