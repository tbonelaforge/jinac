{
    "variables": {
        "prefers_libcpp":"<!(python -c \"import os;import platform;u=platform.uname();print((u[0] == 'Darwin' and int(u[2][0:2]) >= 13) and '-stdlib=libstdc++' not in os.environ.get('CXXFLAGS','') and '-mmacosx-version-min' not in os.environ.get('CXXFLAGS',''))\")"
    },
    "targets" : [
        {
            "target_name"  : "rationalnumber",
            "sources"      : [ "rationalnumber.cc" ],
            "link_settings" : {
                "libraries" : [
                    "-lcln"
                ]
            },
            "conditions": [
                [ '"<(prefers_libcpp)"=="True"', {
                    'xcode_settings': {
                        'MACOSX_DEPLOYMENT_TARGET':'10.9'
                    }
                }]
            ],
        }
    ]   
}
