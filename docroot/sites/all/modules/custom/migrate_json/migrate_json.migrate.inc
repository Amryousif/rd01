<?php

class JSONMigration extends Migration {

/**
 * Abstract constructor
 * @param unknown $arguments
 */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('A custom JSON import module for DNA');
    //list address
    $list_url = 'http://dna.dev:8082/sites/all/modules/custom/migrate_json/itemsList.json' ;
    //pattern to search for entries...
    //$item_url = 'http://dna.dev:8082/sites/all/modules/custom/migrate_json/:id.json' ;
    $fields = array(
    	'id' => 'Unique user ID',
      'name' => 'Full name of user',
      'age' => 'Age of user',
      'gender' => 'Gender of user',
      'first_name' => 'First name of user',
      'last_name' => 'Surname of user'
    );
  //Define the source
  $this->source = new MigrateSourceList(
  //$this->source = new MigrateSourceJSON($list_url, $fields);
      new MigrateSourceJSON($list_url),
      new MigrateItemJSON($item_url, array()),
      $fields
    );

  //Define the destination
  $this->destination = new MigrateDestinationUser();

  //Define the map
  $this->map = new MigrateSQLMap($this->machineName,
    array(
  	  'id' => array(
  	     'type' => 'int',
  	     'not_null' => TRUE,
         )
    ),
    MigrateDestinationUser::getKeySchema()
  );

  //Define the mapping
  $this->addFieldMapping('name', 'name') //users table
    ->sourceMigration('Users');
  $this->addFieldMapping('field_age_value', 'age'); //field_data_field_age table
  $this->addFieldMapping('field_gender_value', 'gender'); //field_data_field_gender table
  //Handle this with explode() in prepareRow
  $this->addFieldMapping('field_first_name_value', 'first_name')
    ->callbacks(array($this, 'fixGender'));
  $this->addFieldMapping('field_last_name_value', 'last_name');

  }

  public function fixGender($gender) {
    if ($gender == "male") return "1";
    if ($gender == "female") return "2";
  }

  public function getFirstName($name){

  }

  public function getSurname($name) {

  }

  public function prepareRow($row){

  }

}
