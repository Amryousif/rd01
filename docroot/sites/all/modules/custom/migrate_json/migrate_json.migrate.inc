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
      'gender' => t('Gender of user; Populated in a callback'),
      'first_name' => t('First name of user; Populated in prepareRow'),
      'last_name' => t('Surname of user; Populated in prepareRow')
    );
  //Define the source
    $this->source = new MigrateSourceJSON($list_url, 'id', $fields);
  //$this->source = new MigrateSourceList(
  //$this->source = new MigrateSourceJSON($list_url, $fields);
  //    new MigrateSourceJSON($list_url),
  //    new MigrateItemJSON($item_url, array()),
  //    $fields
  //  );

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
  $this->addFieldMapping('name', 'name'); //users table
  $this->addFieldMapping('field_age', 'age'); //field_data_field_age table
  $this->addFieldMapping('field_gender', 'gender') //field_data_field_gender table
    ->callbacks(array($this, 'fixGender'));
  $this->addFieldMapping('field_first_name', 'first_name');
  $this->addFieldMapping('field_last_name', 'last_name');

  }

  public function fixGender($gender) {
    if ($gender == "male") return "1";
    if ($gender == "female") return "2";
    return false;
  }

  public function getFirstName($source_name) {
    $exp_name = explode(' ', trim($source_name));
    $first_name = $exp_name[0];
    return $first_name;
  }

  public function getSurname($source_name) {
    $exp_name = explode(' ', $source_name);
    $last_name = array_pop($exp_name);
    return $last_name;
  }

  public function prepareRow($row){
  // included at the beginning of every prepareRow()
    if (parent::prepareRow($row) == FALSE) {
      return FALSE;
    }
    //Massage the data
    $first_name = $this->getFirstName($row->name);
    $last_name = $this->getSurname($row->name);

    //Add the data
    $row->first_name = $first_name;
    $row->last_name = $last_name;
    return TRUE;
  }

}
