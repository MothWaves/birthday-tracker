# Birthday Tracker

A small birthday tracker that lists stored birthdays in order from closest to farthest away.

## Usage
Run `birthday-tracker -h` to get a list with the usage options.

## Configuration
The program uses a json file called `config.json` for configuration, by default stored in the user's home directory under the directory: `.config/birthday-tracker/`

This directory can be changed by setting your desired configuration directory with the Environment Variable: `BIRTHDAY_TRACKER_CONFIG`

The config file currently only has one option `database_path`, which specifies the path to the birthday database json file. 

Example:
```json
{
    "database_path": "/home/henri/Documents/birthdays.json"
}
```

## Birthday Database
The Birthday Database is a json file which should specify an array of json objects, each of which should represent a birthday.

A birthday should specify a name, a day, a month and optionally a year, and have the following format:
```json
{
	"name": "Alex",
	"day": 8,
	"month": 5,
	"year": 1999
}
```
The `year` can also be null, if you don't want to specify the year of birth. If you don't specify the year of birth the program will not include the age the individual is turning on that birthday.

There's also two other optional fields: `important` and `hidden`.

``` json
{
	"name": "Alex",
	"day": 8,
	"month": 5,
	"year": 1999
    "hidden": false,
    "important": true
}
```

If `hidden` is set to true it will not be printed out. This option exists so you can keep birthdays in the database but not have them be displayed. Any other value in `hidden` will be ignored.

`important` will only be considered when running with the `--filter` flag. When filter mode is enabled it will only display birthdays marked as important (with `important` set to true). `important` has no effect outside of that.

## Issues
The "Count days left" features gives results that are incorrect if the birthday is next year (days left are 5 days behind then expected (from regular year to regular year)). This needs to be fixed taking into account leap years and what not.
