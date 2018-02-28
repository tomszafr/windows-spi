{
  "targets": [
    {
      "target_name": "spiCaller",
	  "include_dirs" : [
        "src",
        "<!(node -e \"require('nan')\")"
	  ],
      "sources": [ "src/spiCaller.cc" ]
    }
  ]
}